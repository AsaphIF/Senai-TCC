# Senai-TCC

***Esta é uma parte do TCC apresentado no curso de Técnico em Eletroeletrônica do Senai, feito por <br>
Asaph Ingles Fonseca <br>
Diogo Alves Ferreira <br>
Eduardo Silvestre Padilha<br> 
Gustavo Ferreira Farias <br>
Ubiratan Luzia de Loureiro Junior<br>
Agradecemos ao Professor tutor, Flávio Eduardo de Moraes, que forneceu todos os materiais de apoio, além de sua ajuda constante, e aos outros que nos auxiliaram durante esse projeto, especialmente aos professores de TI George Henrique Sato Wurthmann, o qual forneceu ajuda enquanto fazíamos a programação das placas, assim como o professor Ismael, que nos ajudou com as programações do Google Sheets***

# Introdução
Muitas indústrias têm problemas relacionados a acidentes por falta de preparo ou manutenção das máquinas, estes poderiam ser reduzidos com a implementação de um checklist de segurança feito antes da operação da máquina, de forma que os problemas seriam solucionados sem oferecer risco aos colaboradores que manuseiam o equipamento. A partir disso foi elaborado um produto eficiente, de baixo custo e capaz de otimizar os processos de segurança em geral das empresas. Com a implementação revolucionária do IOT, esse processo se torna mais simples, funcional e sustentável.  Além disso, o produto pode realizar a manutenção preditiva, usando como base o tempo de operação das máquinas e de gráficos que mostram os defeitos mais recorrentes, os processos de classificação através de um checklist online servem como apoio nessa etapa. Sua implementação também gera lucros devido a sua viabilidade em termos redução do tempo de parada das máquinas, baixo custo de instalação e manutenção.  


# Problema de pesquisa
Com a implantação da adequação da NR12 nos tornos da oficina mecânica, dentre os requisitos legais previstas nessa norma, é necessário o preenchimento de checklist de liberação de máquina e esse checklist deve ser feito todas as vezes que se inicia o turno de trabalho, e deve ser armazenado essas informações criando assim um histórico de segurança.

# Objetivos
Desenvolver um sistema baseado em IOT para o preenchimento de formulário de liberação de máquina com níveis de a liberação da máquina com indicação visual pelo sinaleiro pelo usuário, paralelamente um sistema baseado no horímetro da máquina para realizar a manutenção preventiva da máquina. Desenvolver um sistema flexível de forma que possa ser utilizado para qualquer sistema que exija checklist para liberação e até mesmo acompanhamento de manutenção.

# Justificativa
Atender os requisitos legais da NR12 no registro dos checklist de segurança e melhor acompanhamento e programações das manutenções preventivas dos tornos

# Microcontrolador ESP32
Para atender nossa necessidade de conexão à internet e bluetooth, e para não precisarmos integrar o microcontrolador Arduino aos módulos de conexão, constatamos então que o dispositivo que melhor atenderia às nossas necessidades seria o ESP32, pois, diferente do ESP8266 este tem um núcleo de cpu extra, e com isso garante wi-fi mais rápido, mais gpios, além de suportar o bluetooth 4.3.

#  Arduino Nano
A escolha da utilização do Arduino NANO foi devido à pouca necessidade de sua utilização, além da falta de espaço, já que ele só seria utilizado como transmissor e receptor bluetooth integrado no comando do torno, notificando a partida e parada da máquina.













