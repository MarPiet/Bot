#include <stdlib.h>
#include "connect4.h"


/*
	Oma AI-luokka.
*/
class Oma_AI : public C4_AI
{
public:

	// -----------------------------------------------------------------------
	// Oman AI:n toteutus!
	//
	// Pelin tilannetta varten ks. yliluokan C4_AI muuttujat:
	//
	// int _board[COLUMNS][ROWS];	pelilauta, [0][0] on vasen alanurkka
	// int _to_move;				siirtovuoro, RED tai BLUE
	//
	// _board:n arvoina voivat olla vakiot RED (1), BLUE (-1) tai EMPTY (0).
	// Vakiot COLUMNS ja ROWS asettavat pelilaudan dimensiot.
	//
	// Move on periaatteessa vain kokonaisluku, joka kertoo
	// mihin sarakkeesseen kiekko tiputetaan. Sarakkeet numeroidaan
	// vasemmalta oikealle 0,1,2,...
	//
	// Toteuta yliluokan puhtaat virtuaalifunktiot (= 0).
	//
	// Voit luonnollisesti myos lisata omia funktioitasi AI-luokkaasi.
	// Kirjoita kaikkien funktioiden toteutukset tahan samaan tiedostoon.
	// -----------------------------------------------------------------------

	int depth = 7;
	Move select_best_move()
	{
		//Move movelist[COLUMNS];
		//int nof_moves = gen_moves(movelist);

		//// Satunnaisteko‰ly
		//return movelist[rand() % nof_moves];

		// TAI minimaxilla:
		MinMaxVal retval = minimax(this, depth);
		return retval._move;
	}

	void get_AI_name(std::string &name) const
	{
		name = "Kokeilubotti";
	}

	double check_horizontals(int color) {
		double value = 0.0;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++)		{

				if (_board[i][j] == RED && _board[i + 3][j] != BLUE && _board[i + 2][j] != BLUE && _board[i + 1][j] != BLUE)
				{
					if (_board[i + 3][j] == RED || _board[i + 2][j] == RED || _board[i + 1][j] == RED) {
						value += 0.25;
						if (_board[i + 1][j] == RED && _board[i + 2][j] == RED)
							value += 0.5;
						if (_board[i + 2][j] == RED && _board[i + 3][j] == RED)
							value += 0.5;
						if (_board[i + 1][j] == RED && _board[i + 2][j] == RED && _board[i + 3][j] == RED)
							value += 50;
					}

				}
				
				

				if (_board[i][j] == BLUE && _board[i + 3][j] != RED && _board[i + 2][j] != RED && _board[i + 1][j] != RED)
				{
					if (_board[i + 3][j] == BLUE || _board[i + 2][j] == BLUE || _board[i + 1][j] == BLUE) {
						value -= 0.25;
						if (_board[i + 1][j] == BLUE && _board[i + 2][j] == BLUE)
							value -= 0.5;
						if (_board[i + 2][j] == BLUE && _board[i + 3][j] == BLUE)
							value -= 0.5;
						if (_board[i + 1][j] == BLUE && _board[i + 2][j] == BLUE && _board[i + 3][j] == BLUE)
							value -= 50;
					}

				}
					
						

					
		

			}
		}
		return value;
	}

	double check_verticals(int color) {
		double value = 0.0;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {

				//yksi alempana = sama
				if (_board[i][j] == RED && _board[i][j - 1] == RED)
				{
					if (_board[i][j - 2] != RED && j >= 3) {
						
					}
								
					else
						value += 0.5;

					//kaksi alempana sama
					if (_board[i][j - 2] == RED && j <= 4) 
					{
						value += 1;
						if (_board[i][j - 3] == RED)
							value += 50;
						
					}

				}


				//yksi alempana = sama
				if (_board[i][j] == BLUE && _board[i][j - 1] == BLUE)
				{
					if (_board[i][j - 2] != BLUE && j >= 3) {
			
					}
						
					else
						value -= 0.5;

					//kaksi alempana sama
					if (_board[i][j - 2] == BLUE && j <= 4) 
					{
						value -= 1;

						if (_board[i][j - 3] == BLUE)
							value -= 50;
						
														
					}


				}


			}
		}

		return value;
	}

	double check_diagonals(int color) {
		double value = 0.0;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {

			
					if (_board[i][j] == RED && _board[i + 3][j + 3] != BLUE && _board[i + 2][j + 2] != BLUE && _board[i + 1][j + 1] != BLUE)
					{
						if (_board[i + 3][j + 3] == RED || _board[i + 2][j + 2] == RED || _board[i + 1][j + 1] == RED) {
							value += 0.25;
							if (_board[i + 1][j + 1] == RED && _board[i + 2][j + 2] == RED)
								value += 1;
							if (_board[i + 2][j + 2] == RED && _board[i + 3][j + 3] == RED)
								value += 1;
							if (_board[i + 1][j + 1] == RED && _board[i + 2][j + 2] == RED && _board[i + 3][j + 3] == RED)
								value += 50;
						}

					}

			
					if (_board[i][j] == BLUE && _board[i + 3][j + 3] != RED && _board[i + 2][j + 2] != RED && _board[i + 1][j + 1] != RED)
					{
						if (_board[i + 3][j + 3] == BLUE || _board[i + 2][j + 2] == RED || _board[i + 1][j + 1] == RED) {
							value -= 0.25;
							if (_board[i + 1][j + 1] == BLUE && _board[i + 2][j + 2] == BLUE)
								value -= 1;
							if (_board[i + 2][j + 2] == BLUE && _board[i + 3][j + 3] == BLUE)
								value -= 1;
							if (_board[i + 1][j + 1] == BLUE && _board[i + 2][j + 2] == BLUE && _board[i + 3][j + 3] == BLUE)
								value -= 50;
						}

					}





			}
		}

		return value;
	}


	double check_threats() 
	{
		double value = 0.0;
		int redOdd = 0;
		int blueOdd = 0;
		int redEven = 0;
		int blueEven = 0;		
		int mixOdd = 0;
		int mixEven = 0;
		int testcount = 0;

		int redThreats[7][6];
		int blueThreats[7][6];

		int oddThreat = 1;
		int evenThreat = 2;


		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 6; j++) {
				if (_board[i][j] != EMPTY)
					testcount++;
			
			}
		}
		if (testcount == depth)
			value = 1000000;

		
		for (int i = 0; i < COLUMNS; i++) {
			for (int j = 0; j < ROWS; j++) {

					//horizontal
					if (_board[i][j] == RED && _board[i + 1][j] == RED && _board[i + 2][j] == RED && _board[i + 3][j] == EMPTY) 
					{
						if (j % 2 != 0) {
							for(int k = 0; k < j; k++)
								if (blueThreats[i][k] != 2) {
									if (k == j - 1) {
										redOdd++;
										redThreats[i + 3][j] = 1;
									}							
								}
																
						}							
						if (j % 2 == 0)
							for (int k = 0; k < j; k++)
								if (blueThreats[i][k] != 1) {
									if (k == j - 1) {
										redEven++;
										redThreats[i + 3][j] = 2;
									}
								
								}
										
					}

					//horizontal
					if (_board[i][j] == RED && _board[i + 1][j] == RED && _board[i + 2][j] == RED && _board[i - 1][j] == EMPTY) 
					{
						if (j % 2 != 0) {
							for (int k = 0; k < j; k++)
								if (blueThreats[i][k] != 2) {
									if (k == j - 1) {
										redOdd++;
										redThreats[i - 1][j] = 1;
									}
								}

						}
						if (j % 2 == 0)
							for (int k = 0; k < j; k++)
								if (blueThreats[i][k] != 1) {
									if (k == j - 1) {
										redEven++;
										redThreats[i - 1][j] = 2;
									}

								}
					}

					//vertical
					if (_board[i][j] == RED && _board[i][j+1] == RED && _board[i][j+2] == RED && _board[i][j + 3] == EMPTY) 
					{
						if ((j + 3) % 2 != 0) {
							redThreats[i][j + 3] = 1;
							redOdd++;
						}

						if ((j + 3) % 2 == 0) {
							redThreats[i][j + 3] = 2;
							redEven++;
						}
					}

					//diagonal upwards
					if (_board[i][j] == RED && _board[i+1][j + 1] == RED && _board[i+2][j + 2] == RED && _board[i + 3][j + 3] == EMPTY)
					{
						if ((j + 3) % 2 != 0)
							for (int k = 0; k < j + 3; k++) 
								if (blueThreats[i + 3][k] != 2) 
								{
									if (k == j + 2) {
										redOdd++;
										redThreats[i + 3][j + 3] = 1;
									}
										
									
								}
							
						
						if ((j + 3) % 2 == 0)
							for (int k = 0; k < j + 3; k++)
								if (blueThreats[i + 3][k] != 1) 
								{
									if (k == j + 2) {
										redEven++;
										redThreats[i + 3][j + 3] = 2;
									}


								}
					}

					//diagonal upwards
					if (_board[i][j] == RED && _board[i + 1][j + 1] == RED && _board[i + 2][j + 2] == RED && _board[i - 1][j - 1] == EMPTY) {
						if ((j - 1) % 2 != 0)
							for (int k = 0; k < j - 1; k++)
								if (blueThreats[i - 1][k] != 2)
								{
									if (k == j - 2) {
										redOdd++;
										redThreats[i - 1][j - 1] = 1;
									}


								}
						if ((j - 1) % 2 == 0)
							for (int k = 0; k < j - 1; k++)
								if (blueThreats[i - 1][k] != 1)
								{
									if (k == j - 2) {
										redEven++;
										redThreats[i - 1][j - 1] = 2;
									}


								}
					}


					//diagonal downwards
					if (_board[i][j] == RED && _board[i + 1][j - 1] == RED && _board[i + 2][j - 2] == RED && _board[i + 3][j - 3] == EMPTY) {
						if ((j - 3) % 2 != 0)
							for (int k = 0; k < j - 3; k++)
								if (blueThreats[i + 3][k] != 2)
								{
									if (k == j - 4) {
										redOdd++;
										redThreats[i + 3][j - 3] = 1;
									}


								}
						if ((j - 3) % 2 == 0)
							for (int k = 0; k < j - 3; k++)
								if (blueThreats[i + 3][k] != 1)
								{
									if (k == j - 4) {
										redEven++;
										redThreats[i + 3][j - 3] = 2;
									}


								}
					}

					//diagonal downwards
					if (_board[i][j] == RED && _board[i + 1][j - 1] == RED && _board[i + 2][j - 2] == RED && _board[i - 1][j + 1] == EMPTY) {
						if ((j + 1) % 2 != 0)
							for (int k = 0; k < j + 1; k++)
								if (blueThreats[i - 1][k] != 2)
								{
									if (k == j) {
										redOdd++;
										redThreats[i - 1][j + 1] = 1;
									}


								}


						if ((j + 1) % 2 == 0)
							for (int k = 0; k < j + 1; k++)
								if (blueThreats[i - 1][k] != 1)
								{
									if (k == j) {
										redEven++;
										redThreats[i - 1][j + 1] = 2;
									}


								}
					}

					//horizontal
					if (_board[i][j] == BLUE && _board[i + 1][j] == BLUE && _board[i + 2][j] == BLUE && _board[i + 3][j] == EMPTY) {
						if (j % 2 != 0) {
							for (int k = 0; k < j; k++)
								if (redThreats[i][k] != 2) {
									if (k == j - 1) {
										blueOdd++;
										blueThreats[i + 3][j] = 1;
									}
								}

						}
						if (j % 2 == 0)
							for (int k = 0; k < j; k++)
								if (redThreats[i][k] != 1) {
									if (k == j - 1) {
										blueEven++;
										blueThreats[i + 3][j] = 2;
									}

								}
					}

					//horizontal
					if (_board[i][j] == BLUE && _board[i + 1][j] == BLUE && _board[i + 2][j] == BLUE && _board[i - 1][j] == EMPTY) {
						if (j % 2 != 0) {
							for (int k = 0; k < j; k++)
								if (redThreats[i][k] != 2) {
									if (k == j - 1) {
										blueOdd++;
										blueThreats[i - 1][j] = 1;
									}
								}

						}
						if (j % 2 == 0)
							for (int k = 0; k < j; k++)
								if (redThreats[i][k] != 1) {
									if (k == j - 1) {
										blueEven++;
										blueThreats[i - 1][j] = 2;
									}

								}
					}
					//vertical
					if (_board[i][j] == BLUE && _board[i][j + 1] == BLUE && _board[i][j + 2] == BLUE && _board[i][j + 3] == EMPTY) {
						if ((j + 3) % 2 != 0) {
							blueThreats[i][j + 3] = 1;
							blueOdd++;
						}
						
						if ((j + 3) % 2 == 0) {
							blueThreats[i][j + 3] = 2;
							blueEven++;
						}
					}
					//diagonal upwards
					if (_board[i][j] == BLUE && _board[i + 1][j + 1] == BLUE && _board[i + 2][j + 2] == BLUE && _board[i + 3][j + 3] == EMPTY) {
						if ((j + 3) % 2 != 0)
							for (int k = 0; k < j + 3; k++)
								if (redThreats[i + 3][k] != 2)
								{
									if (k == j + 2) {
										blueOdd++;
										blueThreats[i + 3][j + 3] = 1;
									}


								}


						if ((j + 3) % 2 == 0)
							for (int k = 0; k < j + 3; k++)
								if (redThreats[i + 3][k] != 1)
								{
									if (k == j + 2) {
										blueEven++;
										blueThreats[i + 3][j + 3] = 2;
									}


								}
					}
					//diagonal upwards
					if (_board[i][j] == BLUE && _board[i + 1][j + 1] == BLUE && _board[i + 2][j + 2] == BLUE && _board[i - 1][j - 1] == EMPTY) {
						if ((j - 1) % 2 != 0)
							for (int k = 0; k < j - 1; k++)
								if (redThreats[i - 1][k] != 2)
								{
									if (k == j - 2) {
										blueOdd++;
										blueThreats[i - 1][j - 1] = 1;
									}


								}
						if ((j - 1) % 2 == 0)
							for (int k = 0; k < j - 1; k++)
								if (redThreats[i - 1][k] != 1)
								{
									if (k == j - 2) {
										blueEven++;
										blueThreats[i - 1][j - 1] = 2;
									}


								}
					}
					//diagonal downwards
					if (_board[i][j] == BLUE && _board[i + 1][j - 1] == BLUE && _board[i + 2][j - 2] == BLUE && _board[i + 3][j - 3] == EMPTY) {
						if ((j - 3) % 2 != 0)
							for (int k = 0; k < j - 3; k++)
								if (redThreats[i + 3][k] != 2)
								{
									if (k == j - 4) {
										blueOdd++;
										blueThreats[i + 3][j - 3] = 1;
									}


								}
						if ((j - 3) % 2 == 0)
							for (int k = 0; k < j - 3; k++)
								if (redThreats[i + 3][k] != 1)
								{
									if (k == j - 4) {
										blueEven++;
										blueThreats[i + 3][j - 3] = 2;
									}


								}
					}
					//diagonal downwards
					if (_board[i][j] == BLUE && _board[i + 1][j - 1] == BLUE && _board[i + 2][j - 2] == BLUE && _board[i - 1][j + 1] == EMPTY) {
						if ((j + 1) % 2 != 0)
							for (int k = 0; k < j + 1; k++)
								if (redThreats[i - 1][k] != 2)
								{
									if (k == j) {
										blueOdd++;
										blueThreats[i - 1][j + 1] = 1;
									}


								}


						if ((j + 1) % 2 == 0)
							for (int k = 0; k < j + 1; k++)
								if (redThreats[i - 1][k] != 1)
								{
									if (k == j) {
										blueEven++;
										blueThreats[i - 1][j + 1] = 2;
									}


								}
					}



					//mix horizontal
					if (_board[i][j] == RED && _board[i + 1][j] == RED && _board[i + 2][j] == RED && _board[i + 3][j] == EMPTY) {
						if (_board[i][j] == BLUE && _board[i + 1][j] == BLUE && _board[i + 2][j] == BLUE && _board[i + 3][j] == EMPTY) {
							if (j % 2 != 0)
								mixOdd++;
							if (j % 2 == 0)
								mixEven++;
						}
							

					}
					//mix vertical
					if (_board[i][j] == RED && _board[i][j + 1] == RED && _board[i][j + 2] == RED && _board[i][j + 3] == EMPTY) {
						if (_board[i][j] == BLUE && _board[i][j + 1] == BLUE && _board[i][j + 2] == BLUE && _board[i][j + 3] == EMPTY) {
							if ((j + 3) % 2 != 0)
								mixOdd++;
							if ((j + 3) % 2 == 0)
								mixEven++;
						}
							
					}
					// mix diagonal upwards
					if (_board[i][j] == RED && _board[i + 1][j + 1] == RED && _board[i + 2][j + 2] == RED && _board[i + 3][j + 3] == EMPTY) {
						if (_board[i][j] == BLUE && _board[i + 1][j + 1] == BLUE && _board[i + 2][j + 2] == BLUE && _board[i + 3][j + 3] == EMPTY) {
							if ((j + 3) % 2 != 0)
								mixOdd++;
							if ((j + 3) % 2 == 0)
								mixEven++;
						}
							
					}
					//mix diagonal downwards
					if (_board[i][j] == RED && _board[i + 1][j - 1] == RED && _board[i + 2][j - 2] == RED && _board[i + 3][j - 3] == EMPTY) {
						if (_board[i][j] == BLUE && _board[i + 1][j - 1] == BLUE && _board[i + 2][j - 2] == BLUE && _board[i + 3][j - 3] == EMPTY) {
							if ((j + 3) % 2 != 0)
								mixOdd++;
							if ((j + 3) % 2 == 0)
								mixEven++;
						}

					}

					//center value
					if (i == 3) 
					{
						if (_board[i][j] == RED)
							value += 1;
						if (_board[i][j] == BLUE)
							value -= 1;
					}

	

			}
		}

		int odds = redOdd - blueOdd;
		int evens = redEven - blueEven;


		if (redEven > blueEven)
			value += 100;
		if (redOdd > blueOdd)
			value += 100;
		if (blueOdd > redOdd)
			value -= 100;
		if (blueEven > redEven)
			value -= 100;

				
						

		return value;
	}



	double evaluate()
	{
		double value = 0.0;
		value = check_threats();

		return value;
	}


	typedef struct { double _minmax; Move _move; } MinMaxVal;

	MinMaxVal minimax(Oma_AI* p, int depth)
	{
		MinMaxVal retval;
		Move movelist[COLUMNS];
		int nof_moves = gen_moves(movelist);
		retval._minmax = check_result();

		// Rekursion kantatapaus 1 (peli on p‰‰ttynyt)
		if (nof_moves == 0 || retval._minmax != 0)
			return retval;

		// Rekursion kantatapaus 2 (katkaisuvyydess‰)
		if (depth == 0)
		{
			retval._minmax = evaluate();
			return retval;
		}

		// Rekursioaskeleet (kokeillaan siirtovaihtoehdot)
		MinMaxVal best_value;
		best_value._minmax = _to_move == RED ? -1 : 1; // mahdollisimman huono alkuarvo
		for (int i = 0; i < nof_moves; ++i)
		{
			make_move(movelist[i]);
			retval = minimax(this, depth - 1);
			undo_move(movelist[i]);
			if (retval._minmax == 1000000)
			{
				best_value._minmax = retval._minmax;
				best_value._move = 3;
				return best_value;

			}

			if (_to_move == RED && retval._minmax >= best_value._minmax)
			{
				best_value._minmax = retval._minmax;
				best_value._move = movelist[i];
			}
			if (_to_move == BLUE && retval._minmax <= best_value._minmax)
			{
				best_value._minmax = retval._minmax;
				best_value._move = movelist[i];
			}
		}
		return best_value;
	}
};
