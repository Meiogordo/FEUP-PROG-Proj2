Estado de desenvolvimento do trabalho:
- Todos os objetivos apresentados no enunciado foram concretizados com sucesso.

Melhorias implementadas:
- Foi implementado um menu mut�vel, que mostra op��es baseado no conte�do de Menu.txt e chama fun��es baseado no que for definido na fun��o callFunctions em main.cpp; (c�digo do menu em Menu.h e Menu.cpp, classe Menu)
- Foi implementado um detetor de modifica��es n�o gravadas - No caso de o utilizador n�o ter gravado as altera��es que fez aparece um aviso que interroga o utilizador se deseja continuar aquando do carregamento de informa��o de ficheiros ou da sa�da do programa;
- Foi criado um namespace com fun��es genericamente �teis para evitar redefini-las ou ter de ter um objeto de apoio com estas fun��es. Est�o definidas em Utilities.h e Utilities.cpp, dentro do namespace Utilities;
- Foram procuradas solu��es em termos de estrutura��o do programa mais adequadas � situa��o em causa (por exemplo usar maps para guardar as informa��es dos condutores e das linhas, porque facilita uma busca pelo ID, e como este � �nico, n�o � necess�rio usar um multimap);
- Foi adicionada a op��o de iniciar o programa sem carregar ficheiros, estando a mem�ria interna do programa vazia, mas que poder� ser populada com as op��es de adi��o de informa��o;
- O programa � totalmente cross-platform (n�o usa system calls ou fun��es da biblioteca "Windows.h");
- Existe suporte para input e output de carateres de todo o alfabeto latino, incluindo carateres especiais como '�' ou '�', em windows, e suporte para output de carateres em Linux (talvez input tamb�m funcione mas como n�o usamos Linux nem qualquer tipo de sistema Unix n�o pudemos testar isto);
- Ordena��o autom�tica da informa��o dos condutores e linhas por ID, sendo que gravando nos ficheiros com a op��o interna do programa ocorre um "sort" da informa��o por ID, ficando esta ordenada tamb�m no ficheiro.

Notas:
Junto foram enviados dois ficheiros .txt que foram os usados para testar todas as funcionalidades do programa (linhas_test.txt e condutores_test.txt).
Tamb�m existe o ficheiro Menu.txt que deve ser preservado e guardado junto do c�digo pois serve para criar o menu, como descrito acima.