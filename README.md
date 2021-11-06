# Minishell


Ideia para builtins:
 - Antes de iniciar o programa, compilar para uma pasta e adicionar a pasta ao PATH (executar funcao export_inicial). 
 - Quando o comando e chamado (incluindo com pipes) e executado como se fosse um comando de sistema (execve(command path)).
 
 
export PATH=$PATH:/place/with/the/file

Fazer strndup

* Inserir comando: ls -la > file.txt | wc -l

1. Fazer parsing da string ate encontrar um Pipe '|', e guardar na estrutura t_parse.
  1.1 t_parse - Tokens encontrados durante o parsing.
    1.1.1 - t_token Recebe a var c do t_parse, e define que tipo de caracter é, e envia o que encontrou para o t_parse. 
  1.2 Quando encontra um pipe, adiciona o comando ao t_node left, e se nao encontrar mais nenhum Pipe, adiciona o comando final ao 
  t_node right.
  
2. Verificar se tem um comando
  2.1 No caso de existir um comando, guarda-se o comando numa estrutura t_node - É criada uma struct para cada comando individual
  no qual sera guardada o comando, o ficheiro, a redirecao e o quantidade de redireçoes (se existirem). 
  2.2 Dentro da estrutura do comando (t_node), temos mais 2 estruturas:
    2.2.1 t_red - Tipo enum, é um array de tipos de redirecoes consoante a redirecao.
    2.2.2 t_node - Atua como uma linked list (com a proria estrutura dentro da mesma), em que tem duas estruturas t_node 
    (left e right) que vai adicionar os comandos e os respetivos argumentos (incluindo o ficheiro, a redirecao e o quantidade de 
    redireçoes). 
 							
              node
              /		\
             /		 \ 
         ls -la	  wc - l

3. Executar o comando, os comandos do sistema (executaveis dentro do $PATH).
