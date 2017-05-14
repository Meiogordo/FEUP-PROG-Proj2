Estado de desenvolvimento do trabalho:
- Todos os objetivos apresentados no enunciado foram concretizados com sucesso.

Melhorias implementadas:
- Foi implementado um menu mutável, que mostra opções baseado no conteúdo de Menu.txt e chama funções baseado no que for definido na função callFunctions em main.cpp; (código do menu em Menu.h e Menu.cpp, classe Menu)
- Foi implementado um detetor de modificações não gravadas - No caso de o utilizador não ter gravado as alterações que fez aparece um aviso que interroga o utilizador se deseja continuar aquando do carregamento de informação de ficheiros ou da saída do programa;
- Foi criado um namespace com funções genericamente úteis para evitar redefini-las ou ter de ter um objeto de apoio com estas funções. Estão definidas em Utilities.h e Utilities.cpp, dentro do namespace Utilities;
- Foram procuradas soluções em termos de estruturação do programa mais adequadas à situação em causa (por exemplo usar maps para guardar as informações dos condutores e das linhas, porque facilita uma busca pelo ID, e como este é único, não é necessário usar um multimap);
- Foi adicionada a opção de iniciar o programa sem carregar ficheiros, estando a memória interna do programa vazia, mas que poderá ser populada com as opções de adição de informação;
- O programa é totalmente cross-platform (não usa system calls ou funções da biblioteca "Windows.h");
- Existe suporte para input e output de carateres de todo o alfabeto latino, incluindo carateres especiais como 'ç' ou 'ã', em windows, e suporte para output de carateres em Linux (talvez input também funcione mas como não usamos Linux nem qualquer tipo de sistema Unix não pudemos testar isto);
- Ordenação automática da informação dos condutores e linhas por ID, sendo que gravando nos ficheiros com a opção interna do programa ocorre um "sort" da informação por ID, ficando esta ordenada também no ficheiro.

Notas:
Junto foram enviados dois ficheiros .txt que foram os usados para testar todas as funcionalidades do programa (linhas_test.txt e condutores_test.txt).
Também existe o ficheiro Menu.txt que deve ser preservado e guardado junto do código pois serve para criar o menu, como descrito acima.