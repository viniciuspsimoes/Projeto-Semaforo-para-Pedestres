# Projeto-Semaforo-para-Pedestres
Consiste em utilizar um microcontrolador, esp 32, para simular um sémaforo de transito comum.
Porém, esse codigo possui exigencias:

Especificações:

Quando se acionar o botão, o sistema deverá emitir um sinal sonoro de confirmação.
Após o botão de pedestres ser acionado, o semáforo de pedestres deverá aguardar, entre 10 e
60 segundos para abrir, a depender da última abertura.
Ao se abrir o semáforo de pedestres, um sinal sonoro deverá ser emitido. E uma mensagem
deve ser enviada a um Display de LCD informando que a travessia pode ser feita com
segurança. O display de LCD também deverá informar o tempo restante para abertura do sinal.
A frequência do sinal sonoro deverá variar até que o tempo de abertura do semáforo se esgote
(30 segundos).
Caso algum automóvel ultrapasse o sinal vermelho, uma foto deverá ser capturada e uma
variável “multas” deverá ser incrementada.

OBS: Nenhum pedestre aperta uma única vez o botão do semáforo para que ele se abra... Não
será o número de apertos de botão que fará com que o semáforo de pedestres se abra mais
rápido. Só deverá ser computado o primeiro aperto na condição de semáforo fechado.

O Project.c é para ser rodado no proprio wokwi.
