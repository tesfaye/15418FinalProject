chess: Piece.cpp Player.cpp BoardState.cpp main.cpp
	g++ -std=c++11 -fcilkplus *.cpp -o chess

clean:
	rm -f chess

submit:
	cd templates && ../scripts/batch_generate.sh
	cd job_outputs && ../scripts/sub/submit.sh
