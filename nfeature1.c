#include <SFML/Graphics.hpp>
#include <windows.h>
int scoreReg[4] = {0,0,0,0}; //score 1, score 2,
void main() {
  sf::RenderWindow window(sf::VideoMode(700, 700), "Small Pong Program");
    sf::Font font; //Set font
      font.loadFromFile("arial.ttf");
        sf::Text text; //Set text
	  text.setFont(font);
	    text.setColor(sf::Color::Green);
	      text.setCharacterSize(24);
	        text.setPosition(10,10);
		  sf::CircleShape ballShape(5.0f,12); //Ball shape
		    sf::RectangleShape paddleShape;     //Paddle shape
		      sf::Vector2f size(100,15);  //BEGIN GOTO LABEL BELOW
		        //Top paddle, bottom paddle, ball, ball vel, reg a, reg b
			  begin: float positions[8] = {310,50,310,635,345,342.5,0.5,0.5};
			    if(scoreReg[0] == 5){text.setString("Top player wins!"); //Top Player wins
			        goto end;}
				  if(scoreReg[1] == 5){text.setString("Bottom player wins!"); //Bottom wins
				      goto end;}
				        paddleShape.setSize(size);
					  ballShape.setPosition(positions[4], positions[5]);
					    ballShape.setFillColor(sf::Color::Red);
					      while (window.isOpen()) {
					          sf::Event event;
						      while (window.pollEvent(event)) //Event loop for window close
						              if (event.type == sf::Event::Closed) 
							                window.close();
									    //Top player controls
									        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) positions[0] -= 1;
										    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))positions[0] += 1;
										        //Bottom player controls
											    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))positions[2] -= 1;
											        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))positions[2] += 1;
												    if(positions[4] <=0 || positions[4] >=695) //Ball collision with sides
												          positions[6] = positions[6]*-1;          //Flip ball x vel
													      if(positions[5] < 5){ //Yes kill me goto
													            scoreReg[1] += 1;
														          goto begin;} //New ball and add 1 point to bottom player
															      else if (positions[5] > 695){ //Yes kill me goto
															            scoreReg[0] += 1;
																          goto begin;} //New ball and add 1 point to top player
																	      positions[4] += positions[6]; //Update ball pos x
																	          positions[5] += positions[7]; //Update ball pos y
																		      ballShape.setPosition(positions[4], positions[5]);  //Set ball pos
																		          for(int i=0; i<3; i+=2){ //Brilliant idea offset using for loop i
																			        if(positions[4]+5 < positions[i]) continue; //x left
																				      else if (positions[4] >positions[i] + size.x) continue; //x right
																				            if(positions[5]+5 < positions[i+1]) continue; //x left
																					          else if (positions[5] >positions[i+1] + size.y) continue; //x right
																						        positions[7] = positions[7]*-1;}//Collision occured reverse ball
																							    std::string score = std::to_string(scoreReg[0]) + " : " +
																							        std::to_string(scoreReg[1]);
																								    text.setString(score);
																								        paddleShape.setPosition(positions[0], positions[1]);
																									    window.draw(paddleShape); //Draw top paddle
																									        paddleShape.setPosition(positions[2], positions[3]);
																										    window.draw(paddleShape); //Draw bottom paddle
																										        window.draw(ballShape);
																											    window.draw(text);
																											        window.display();
																												    window.clear(); // Clear and then draw everything
																												        Sleep(2);}
																													  end:;  //GOTO END LABEL    
																													    window.draw(text);
																													      window.display();
																													        Sleep(5000);}

