Estado de desenvolvimento do trabalho:
- Todos os objetivos apresentados no enunciado foram concretizados com sucesso.

Melhorias implementadas:
- Foi implementado um menu mutável, que mostra opções baseado no conteúdo de Menu.txt e chama funções baseado no que for definido na função callFunctions em main.cpp; (código do menu em Menu.h e Menu.cpp, classe Menu)
- Foi implementado um detetor de modificações não gravadas - No caso de o utilizador não ter gravado as alterações que fez aparece um aviso que interroga o utilizador se deseja continuar aquando do carregamento de informação de ficheiros ou da saída do programa;
- Foi criado um namespace com funções genericamente úteis para evitar redefini-las ou ter de ter um objeto de apoio com estas funções. Estão definidas em Utilities.h e Utilities.cpp, dentro do namespace Utilities;
- O código relativo à gestão da empresa de autocarros foi colocado, para ser mais modular e organizado, dentro da classe BusManager, em BusManager.h e BusManager.cpp;
- Foi adicionada a opção de iniciar o programa sem carregar ficheiros, estando a memória interna do programa vazia, mas que poderá ser populada com as opções de adicionar linha e de adicionar condutores.

Nota:
Junto foram enviados dois ficheiros .txt que foram os usados para testar todas as funcionalidades do programa (linhas_test.txt e condutores_test.txt).