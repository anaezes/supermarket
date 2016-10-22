
* Notas sobre compilação:
  1) Programado em linux
  2) Testado e compilado em Linux e Windows (linha de comandos Cygwin)

  Compilar em linux:
  g++ -Wall -std=c++11 main.cpp Supermarket.cpp Menu.cpp Customer.cpp Transaction.cpp Product.cpp Date.cpp Recommendation.cpp -o trabalho2

* Estado de desenvolvimento:
  Foram cumpridos todos os objectivos.

* Melhorias implementadas:
  - Output formatado (tabelas, etc).
  - Opção para acrescentar produtos.

* Recomendação para um cliente feita da seguinte forma:
      1) Pedir ao utilizador para introduzir o id do cliente a quem fazer publicidade.
      2) Calcular o racio de parecença do cliente escolhido com todos os outros.
      3) Se o racio de parecença for maior ou igual ao definido(valor estático = 60%), fazer recomendação:
      	 - Para recomendar ao cliente escolhido, A, apartir de um outro B, são escolhidos todos os produtos que
	 o B tenha comprado e o A não.
* Recomendação para Bottom10 feita como descrita no enunciado:
      1) Criar matriz dos bottom10.
      2) Recolher clientes interessantes (que tenham comprado todos os produtos comuns do bottom10 + 1).
      3) Recolher produtos dos clientes interessantes e quantos desses clientes os compraram.
      4) Recomendar o produto que não seja comum nos bottom10 e que seja o mais comprado entre os outros.

