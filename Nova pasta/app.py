import os
import sqlite3
from flask import Flask, render_template, request, redirect, url_for, flash, send_from_directory, session
from werkzeug.utils import secure_filename
from datetime import datetime
import uuid
from functools import wraps

app = Flask(__name__)
app.secret_key = os.getenv('SECRET_KEY', 'jotinha_veiculos_secret_key_2024')

# Configurações
UPLOAD_FOLDER = 'static/uploads'
ALLOWED_EXTENSIONS = {'png', 'jpg', 'jpeg', 'gif', 'webp'}
app.config['UPLOAD_FOLDER'] = UPLOAD_FOLDER

# Credenciais do administrador (em produção, use hash de senha)
ADMIN_USERNAME = 'admin'
ADMIN_PASSWORD = 'jotinha123'

# Criar pasta de uploads se não existir
os.makedirs(UPLOAD_FOLDER, exist_ok=True)

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

def get_db_connection():
    conn = sqlite3.connect('instance/database.db')
    conn.row_factory = sqlite3.Row
    return conn

def init_db():
    conn = get_db_connection()
    conn.execute('''
        CREATE TABLE IF NOT EXISTS veiculos (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            marca TEXT NOT NULL,
            modelo TEXT NOT NULL,
            ano INTEGER NOT NULL,
            preco REAL NOT NULL,
            imagem TEXT,
            descricao TEXT,
            quilometragem INTEGER,
            combustivel TEXT,
            cambio TEXT,
            cor TEXT,
            destaque INTEGER DEFAULT 0,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
        )
    ''')
    
    # Nova tabela para múltiplas imagens
    conn.execute('''
        CREATE TABLE IF NOT EXISTS veiculo_imagens (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            veiculo_id INTEGER NOT NULL,
            imagem TEXT NOT NULL,
            ordem INTEGER DEFAULT 0,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (veiculo_id) REFERENCES veiculos (id) ON DELETE CASCADE
        )
    ''')
    
    conn.commit()
    conn.close()

def format_price(price):
    return f"R$ {price:,.2f}".replace(',', 'X').replace('.', ',').replace('X', '.')

def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if 'admin_logged_in' not in session:
            flash('Você precisa fazer login para acessar esta área.', 'error')
            return redirect(url_for('admin_login'))
        return f(*args, **kwargs)
    return decorated_function

def get_veiculo_imagens(veiculo_id):
    """Busca todas as imagens de um veículo"""
    conn = get_db_connection()
    imagens = conn.execute('''
        SELECT * FROM veiculo_imagens 
        WHERE veiculo_id = ? 
        ORDER BY ordem ASC, created_at ASC
    ''', (veiculo_id,)).fetchall()
    conn.close()
    return imagens

@app.route('/')
def index():
    conn = get_db_connection()
    # Buscar veículos em destaque com suas primeiras imagens
    veiculos = conn.execute('''
        SELECT v.*, vi.imagem as primeira_imagem 
        FROM veiculos v 
        LEFT JOIN veiculo_imagens vi ON v.id = vi.veiculo_id AND vi.ordem = 0
        WHERE v.destaque = 1 
        ORDER BY v.created_at DESC 
        LIMIT 6
    ''').fetchall()
    conn.close()
    return render_template('index.html', veiculos=veiculos, format_price=format_price)

@app.route('/veiculos')
def veiculos_list():
    # Filtros
    marca = request.args.get('marca', '').strip()
    ano = request.args.get('ano', '').strip()
    combustivel = request.args.get('combustivel', '').strip()
    cambio = request.args.get('cambio', '').strip()
    cor = request.args.get('cor', '').strip()
    preco_min = request.args.get('preco_min', '').strip()
    preco_max = request.args.get('preco_max', '').strip()
    
    # Parâmetros de paginação
    page = request.args.get('page', 1, type=int)
    per_page = 12  # 12 veículos por página

    query = '''
        SELECT v.*, vi.imagem as primeira_imagem 
        FROM veiculos v 
        LEFT JOIN veiculo_imagens vi ON v.id = vi.veiculo_id AND vi.ordem = 0
        WHERE 1=1
    '''
    params = []
    if marca:
        query += ' AND v.marca LIKE ?'
        params.append(f'%{marca}%')
    if ano:
        query += ' AND v.ano = ?'
        params.append(ano)
    if combustivel:
        query += ' AND v.combustivel = ?'
        params.append(combustivel)
    if cambio:
        query += ' AND v.cambio = ?'
        params.append(cambio)
    if cor:
        query += ' AND v.cor LIKE ?'
        params.append(f'%{cor}%')
    if preco_min:
        query += ' AND v.preco >= ?'
        params.append(preco_min.replace(',', '.'))
    if preco_max:
        query += ' AND v.preco <= ?'
        params.append(preco_max.replace(',', '.'))
    
    # Query para contar total
    count_query = query.replace('SELECT v.*, vi.imagem as primeira_imagem', 'SELECT COUNT(*) as total')
    
    conn = get_db_connection()
    
    # Contar total de veículos com filtros
    total_veiculos = conn.execute(count_query, params).fetchone()['total']
    
    # Calcular offset para paginação
    offset = (page - 1) * per_page
    
    # Adicionar ordenação e paginação
    query += ' ORDER BY v.created_at DESC LIMIT ? OFFSET ?'
    params.extend([per_page, offset])
    
    veiculos = conn.execute(query, params).fetchall()
    
    # Para filtros dinâmicos
    marcas = [row['marca'] for row in conn.execute('SELECT DISTINCT marca FROM veiculos').fetchall()]
    anos = [row['ano'] for row in conn.execute('SELECT DISTINCT ano FROM veiculos ORDER BY ano DESC').fetchall()]
    combustiveis = [row['combustivel'] for row in conn.execute('SELECT DISTINCT combustivel FROM veiculos WHERE combustivel IS NOT NULL AND combustivel != ""').fetchall()]
    cambios = [row['cambio'] for row in conn.execute('SELECT DISTINCT cambio FROM veiculos WHERE cambio IS NOT NULL AND cambio != ""').fetchall()]
    cores = [row['cor'] for row in conn.execute('SELECT DISTINCT cor FROM veiculos WHERE cor IS NOT NULL AND cor != ""').fetchall()]
    
    # Calcular informações de paginação
    total_pages = (total_veiculos + per_page - 1) // per_page
    has_prev = page > 1
    has_next = page < total_pages
    
    conn.close()
    
    return render_template('veiculos.html', 
                         veiculos=veiculos, 
                         marcas=marcas, 
                         anos=anos, 
                         combustiveis=combustiveis, 
                         cambios=cambios, 
                         cores=cores, 
                         format_price=format_price,
                         page=page,
                         total_pages=total_pages,
                         has_prev=has_prev,
                         has_next=has_next,
                         total_veiculos=total_veiculos,
                         # Manter filtros ativos
                         marca=marca,
                         ano=ano,
                         combustivel=combustivel,
                         cambio=cambio,
                         cor=cor,
                         preco_min=preco_min,
                         preco_max=preco_max)

@app.route('/veiculo/<int:id>')
def veiculo_detalhes(id):
    conn = get_db_connection()
    veiculo = conn.execute('SELECT * FROM veiculos WHERE id = ?', (id,)).fetchone()
    conn.close()
    
    if veiculo is None:
        flash('Veículo não encontrado!', 'error')
        return redirect(url_for('index'))
    
    # Buscar todas as imagens do veículo
    imagens = get_veiculo_imagens(id)
    
    return render_template('veiculo_detalhes.html', veiculo=veiculo, imagens=imagens, format_price=format_price)

@app.route('/contato')
def contato():
    return render_template('contato.html')

@app.route('/admin/login', methods=['GET', 'POST'])
def admin_login():
    if request.method == 'POST':
        username = request.form['username']
        password = request.form['password']
        
        if username == ADMIN_USERNAME and password == ADMIN_PASSWORD:
            session['admin_logged_in'] = True
            flash('Login realizado com sucesso!', 'success')
            return redirect(url_for('admin_dashboard'))
        else:
            flash('Usuário ou senha incorretos!', 'error')
    
    return render_template('admin/login.html')

@app.route('/admin/logout')
def admin_logout():
    session.pop('admin_logged_in', None)
    flash('Logout realizado com sucesso!', 'success')
    return redirect(url_for('index'))

@app.route('/admin')
@login_required
def admin_dashboard():
    # Parâmetros de paginação
    page = request.args.get('page', 1, type=int)
    per_page = 10  # 10 veículos por página
    
    conn = get_db_connection()
    
    # Contar total de veículos
    total_veiculos = conn.execute('SELECT COUNT(*) as total FROM veiculos').fetchone()['total']
    
    # Calcular offset para paginação
    offset = (page - 1) * per_page
    
    # Buscar veículos com paginação
    veiculos = conn.execute('''
        SELECT v.*, vi.imagem as primeira_imagem 
        FROM veiculos v 
        LEFT JOIN veiculo_imagens vi ON v.id = vi.veiculo_id AND vi.ordem = 0
        ORDER BY v.created_at DESC
        LIMIT ? OFFSET ?
    ''', (per_page, offset)).fetchall()
    
    # Calcular informações de paginação
    total_pages = (total_veiculos + per_page - 1) // per_page
    has_prev = page > 1
    has_next = page < total_pages
    
    # Buscar estatísticas gerais (todos os veículos)
    veiculos_destaque = conn.execute('SELECT COUNT(*) as total FROM veiculos WHERE destaque = 1').fetchone()['total']
    valor_total = conn.execute('SELECT SUM(preco) as total FROM veiculos').fetchone()['total'] or 0
    
    # Buscar o veículo mais caro
    veiculo_mais_caro = conn.execute('''
        SELECT marca, modelo, preco 
        FROM veiculos 
        WHERE preco = (SELECT MAX(preco) FROM veiculos)
        LIMIT 1
    ''').fetchone()
    
    preco_mais_caro = veiculo_mais_caro['preco'] if veiculo_mais_caro else 0
    marca_mais_cara = veiculo_mais_caro['marca'] if veiculo_mais_caro else ''
    modelo_mais_caro = veiculo_mais_caro['modelo'] if veiculo_mais_caro else ''
    
    conn.close()
    
    return render_template('admin/dashboard.html', 
                         veiculos=veiculos, 
                         total_veiculos=total_veiculos,
                         veiculos_destaque=veiculos_destaque,
                         valor_total=valor_total,
                         preco_mais_caro=preco_mais_caro,
                         marca_mais_cara=marca_mais_cara,
                         modelo_mais_caro=modelo_mais_caro,
                         format_price=format_price,
                         page=page,
                         total_pages=total_pages,
                         has_prev=has_prev,
                         has_next=has_next)

@app.route('/admin/veiculo/novo', methods=['GET', 'POST'])
@login_required
def novo_veiculo():
    if request.method == 'POST':
        marca = request.form['marca'].strip()
        modelo = request.form['modelo'].strip()
        ano = request.form['ano']
        preco = request.form['preco']
        descricao = request.form['descricao'].strip()
        quilometragem = request.form['quilometragem']
        combustivel = request.form['combustivel']
        cambio = request.form['cambio']
        cor = request.form['cor'].strip()
        destaque = request.form.get('destaque', 0)  # Checkbox não marcado = 0, marcado = 1
        imagens = request.files.getlist('imagens')
        
        # Verificar limite de destaque se tentar adicionar aos destaques
        if destaque:
            conn = get_db_connection()
            veiculos_destaque = conn.execute('SELECT COUNT(*) as total FROM veiculos WHERE destaque = 1').fetchone()
            conn.close()
            if veiculos_destaque['total'] >= 6:
                flash('Limite de 6 veículos em destaque atingido! Remova algum veículo dos destaques antes de adicionar este.', 'error')
                return render_template('admin/form.html', veiculo=None, limite_destaque=True)
        
        # Validação básica
        errors = []
        if not marca:
            errors.append('Marca é obrigatória')
        if not modelo:
            errors.append('Modelo é obrigatório')
        if not ano or not ano.isdigit() or int(ano) < 1900 or int(ano) > datetime.now().year + 1:
            errors.append('Ano deve ser um número válido')
        if not preco or not preco.replace('.', '').replace(',', '').isdigit():
            errors.append('Preço deve ser um número válido')
        
        if errors:
            for error in errors:
                flash(error, 'error')
            return render_template('admin/form.html', veiculo=None)
        
        # Processar preço
        preco = float(preco.replace(',', '.'))
        
        # Processar quilometragem
        quilometragem = int(quilometragem) if quilometragem and quilometragem.isdigit() else 0
        
        # Salvar no banco
        conn = get_db_connection()
        cursor = conn.cursor()
        cursor.execute('''
            INSERT INTO veiculos (marca, modelo, ano, preco, imagem, descricao, quilometragem, combustivel, cambio, cor, destaque)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
        ''', (marca, modelo, int(ano), preco, None, descricao, quilometragem, combustivel, cambio, cor, destaque))
        
        veiculo_id = cursor.lastrowid
        
        # Processar imagens
        imagem_principal = None
        for i, imagem in enumerate(imagens):
            if imagem and imagem.filename != '':
                if allowed_file(imagem.filename):
                    ext = imagem.filename.rsplit('.', 1)[1].lower()
                    filename = f"{uuid.uuid4().hex}.{ext}"
                    imagem.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
                    
                    # Primeira imagem será a principal
                    if i == 0:
                        imagem_principal = filename
                    
                    # Salvar na tabela de imagens
                    cursor.execute('''
                        INSERT INTO veiculo_imagens (veiculo_id, imagem, ordem)
                        VALUES (?, ?, ?)
                    ''', (veiculo_id, filename, i))
                else:
                    flash(f'Tipo de arquivo não permitido para {imagem.filename}. Use: png, jpg, jpeg, gif, webp', 'error')
        
        # Atualizar imagem principal no veículo
        if imagem_principal:
            cursor.execute('UPDATE veiculos SET imagem = ? WHERE id = ?', (imagem_principal, veiculo_id))
        
        conn.commit()
        conn.close()
        
        flash('Veículo cadastrado com sucesso!', 'success')
        return redirect(url_for('admin_dashboard'))
    
    # Verificar se há limite de destaque para o formulário
    conn = get_db_connection()
    veiculos_destaque = conn.execute('SELECT COUNT(*) as total FROM veiculos WHERE destaque = 1').fetchone()['total']
    limite_destaque = veiculos_destaque >= 6
    conn.close()
    
    # Adicionar warning se estiver próximo do limite
    if veiculos_destaque == 5:
        flash('Atenção: Você tem 5 veículos em destaque. O limite máximo é 6.', 'warning')
    elif veiculos_destaque == 0:
        flash('Dica: Adicione veículos aos destaques para que apareçam na página inicial.', 'info')
    
    return render_template('admin/form.html', veiculo=None, limite_destaque=limite_destaque)

@app.route('/admin/veiculo/editar/<int:id>', methods=['GET', 'POST'])
@login_required
def editar_veiculo(id):
    conn = get_db_connection()
    veiculo = conn.execute('SELECT * FROM veiculos WHERE id = ?', (id,)).fetchone()
    conn.close()
    
    if veiculo is None:
        flash('Veículo não encontrado!', 'error')
        return redirect(url_for('admin_dashboard'))
    
    if request.method == 'POST':
        marca = request.form['marca'].strip()
        modelo = request.form['modelo'].strip()
        ano = request.form['ano']
        preco = request.form['preco']
        descricao = request.form['descricao'].strip()
        quilometragem = request.form['quilometragem']
        combustivel = request.form['combustivel']
        cambio = request.form['cambio']
        cor = request.form['cor'].strip()
        destaque = request.form.get('destaque', 0)  # Checkbox não marcado = 0, marcado = 1
        imagens = request.files.getlist('imagens')
        
        # Verificar limite de destaque se tentar adicionar aos destaques (e não estava antes)
        if destaque and not veiculo['destaque']:
            conn = get_db_connection()
            veiculos_destaque = conn.execute('SELECT COUNT(*) as total FROM veiculos WHERE destaque = 1').fetchone()
            conn.close()
            if veiculos_destaque['total'] >= 6:
                flash('Limite de 6 veículos em destaque atingido! Remova algum veículo dos destaques antes de adicionar este.', 'error')
                imagens = get_veiculo_imagens(id)
                return render_template('admin/form.html', veiculo=veiculo, imagens=imagens, limite_destaque=True)
        
        # Validação básica
        errors = []
        if not marca:
            errors.append('Marca é obrigatória')
        if not modelo:
            errors.append('Modelo é obrigatório')
        if not ano or not ano.isdigit() or int(ano) < 1900 or int(ano) > datetime.now().year + 1:
            errors.append('Ano deve ser um número válido')
        if not preco or not preco.replace('.', '').replace(',', '').isdigit():
            errors.append('Preço deve ser um número válido')
        
        if errors:
            for error in errors:
                flash(error, 'error')
            return render_template('admin/form.html', veiculo=veiculo)
        
        # Processar preço
        preco = float(preco.replace(',', '.'))
        
        # Processar quilometragem
        quilometragem = int(quilometragem) if quilometragem and quilometragem.isdigit() else 0
        
        # Atualizar no banco
        conn = get_db_connection()
        cursor = conn.cursor()
        cursor.execute('''
            UPDATE veiculos SET marca = ?, modelo = ?, ano = ?, preco = ?, 
            descricao = ?, quilometragem = ?, combustivel = ?, cambio = ?, cor = ?, destaque = ? WHERE id = ?
        ''', (marca, modelo, int(ano), preco, descricao, quilometragem, combustivel, cambio, cor, destaque, id))
        
        # Processar novas imagens
        if imagens and any(img.filename for img in imagens):
            # Buscar imagens existentes para determinar a ordem
            imagens_existentes = get_veiculo_imagens(id)
            ordem_inicial = len(imagens_existentes)
            
            for i, imagem in enumerate(imagens):
                if imagem and imagem.filename != '':
                    if allowed_file(imagem.filename):
                        ext = imagem.filename.rsplit('.', 1)[1].lower()
                        filename = f"{uuid.uuid4().hex}.{ext}"
                        imagem.save(os.path.join(app.config['UPLOAD_FOLDER'], filename))
                        
                        # Salvar na tabela de imagens
                        cursor.execute('''
                            INSERT INTO veiculo_imagens (veiculo_id, imagem, ordem)
                            VALUES (?, ?, ?)
                        ''', (id, filename, ordem_inicial + i))
                    else:
                        flash(f'Tipo de arquivo não permitido para {imagem.filename}. Use: png, jpg, jpeg, gif, webp', 'error')
        
        conn.commit()
        conn.close()
        
        flash('Veículo atualizado com sucesso!', 'success')
        return redirect(url_for('admin_dashboard'))
    
    # Buscar imagens existentes
    imagens = get_veiculo_imagens(id)
    
    # Verificar se há limite de destaque para o formulário
    conn = get_db_connection()
    veiculos_destaque = conn.execute('SELECT COUNT(*) as total FROM veiculos WHERE destaque = 1').fetchone()['total']
    limite_destaque = veiculos_destaque >= 6 and not veiculo['destaque']
    conn.close()
    
    # Adicionar warning se estiver próximo do limite
    if veiculos_destaque == 5:
        flash('Atenção: Você tem 5 veículos em destaque. O limite máximo é 6.', 'warning')
    elif veiculos_destaque == 0:
        flash('Dica: Adicione veículos aos destaques para que apareçam na página inicial.', 'info')
    
    return render_template('admin/form.html', veiculo=veiculo, imagens=imagens, limite_destaque=limite_destaque)

@app.route('/admin/veiculo/excluir/<int:id>', methods=['POST'])
@login_required
def excluir_veiculo(id):
    conn = get_db_connection()
    veiculo = conn.execute('SELECT * FROM veiculos WHERE id = ?', (id,)).fetchone()
    
    if veiculo is None:
        flash('Veículo não encontrado!', 'error')
        return redirect(url_for('admin_dashboard'))
    
    # Buscar todas as imagens do veículo
    imagens = get_veiculo_imagens(id)
    
    # Deletar imagens do servidor
    for img in imagens:
        image_path = os.path.join(app.config['UPLOAD_FOLDER'], img['imagem'])
        if os.path.exists(image_path):
            os.remove(image_path)
    
    # Deletar do banco (CASCADE irá deletar as imagens automaticamente)
    conn.execute('DELETE FROM veiculos WHERE id = ?', (id,))
    conn.commit()
    conn.close()
    
    flash('Veículo excluído com sucesso!', 'success')
    return redirect(url_for('admin_dashboard'))

@app.route('/admin/veiculo/toggle-destaque/<int:id>', methods=['POST'])
@login_required
def toggle_destaque(id):
    conn = get_db_connection()
    veiculo = conn.execute('SELECT * FROM veiculos WHERE id = ?', (id,)).fetchone()
    
    if veiculo is None:
        flash('Veículo não encontrado!', 'error')
        return redirect(url_for('admin_dashboard'))
    
    # Se o veículo já está em destaque, pode remover normalmente
    if veiculo['destaque']:
        novo_status = 0
        conn.execute('UPDATE veiculos SET destaque = ? WHERE id = ?', (novo_status, id))
        conn.commit()
        conn.close()
        flash('Veículo removido dos destaques com sucesso!', 'success')
        return redirect(url_for('admin_dashboard'))
    
    # Se vai adicionar aos destaques, verificar o limite
    veiculos_destaque = conn.execute('SELECT COUNT(*) as total FROM veiculos WHERE destaque = 1').fetchone()
    if veiculos_destaque['total'] >= 6:
        conn.close()
        flash('Limite de 6 veículos em destaque atingido! Remova algum veículo dos destaques antes de adicionar este.', 'error')
        return redirect(url_for('admin_dashboard'))
    
    # Adicionar aos destaques
    novo_status = 1
    conn.execute('UPDATE veiculos SET destaque = ? WHERE id = ?', (novo_status, id))
    conn.commit()
    conn.close()
    
    flash('Veículo adicionado aos destaques com sucesso!', 'success')
    return redirect(url_for('admin_dashboard'))

@app.route('/admin/veiculo/imagem/excluir/<int:imagem_id>', methods=['POST'])
@login_required
def excluir_imagem(imagem_id):
    conn = get_db_connection()
    imagem = conn.execute('SELECT * FROM veiculo_imagens WHERE id = ?', (imagem_id,)).fetchone()
    
    if imagem is None:
        flash('Imagem não encontrada!', 'error')
        return redirect(url_for('admin_dashboard'))
    
    veiculo_id = imagem['veiculo_id']
    
    try:
        # Deletar arquivo do servidor
        image_path = os.path.join(app.config['UPLOAD_FOLDER'], imagem['imagem'])
        if os.path.exists(image_path):
            os.remove(image_path)
        
        # Deletar do banco
        conn.execute('DELETE FROM veiculo_imagens WHERE id = ?', (imagem_id,))
        
        # Reordenar as imagens restantes
        imagens_restantes = conn.execute('SELECT * FROM veiculo_imagens WHERE veiculo_id = ? ORDER BY ordem ASC, created_at ASC', (veiculo_id,)).fetchall()
        
        for idx, img in enumerate(imagens_restantes):
            conn.execute('UPDATE veiculo_imagens SET ordem = ? WHERE id = ?', (idx, img['id']))
        
        # Atualizar imagem principal
        nova_principal = conn.execute('SELECT * FROM veiculo_imagens WHERE veiculo_id = ? ORDER BY ordem ASC LIMIT 1', (veiculo_id,)).fetchone()
        if nova_principal:
            conn.execute('UPDATE veiculos SET imagem = ? WHERE id = ?', (nova_principal['imagem'], veiculo_id))
        else:
            conn.execute('UPDATE veiculos SET imagem = NULL WHERE id = ?', (veiculo_id,))
        
        conn.commit()
        flash('Imagem excluída com sucesso!', 'success')
    except Exception as e:
        flash(f'Erro ao excluir imagem: {str(e)}', 'error')
    finally:
        conn.close()
    
    return redirect(url_for('editar_veiculo', id=veiculo_id))

@app.route('/uploads/<filename>')
def uploaded_file(filename):
    return send_from_directory(app.config['UPLOAD_FOLDER'], filename)

if __name__ == '__main__':
    init_db()
    app.run(debug=True) 