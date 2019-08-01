// Mohammad Asif Zaman
// July 2019
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <time.h>
using namespace sf;


const Color dead_cell(26,27,29);
// const Color live_cell(2,252,251);
const Color live_cell(152,121,2);



const unsigned int cell_size_x = 5;
const unsigned int cell_size_y = 5;

const unsigned int offset_x = 0;
const unsigned int offset_y = 5;

const unsigned int cell_border_thickness = 1;


const unsigned int window_size_x = 620;
const unsigned int window_size_y = 620;
const unsigned int window_extra_y = 60;

const unsigned int Nx = window_size_x/cell_size_x;
const unsigned int Ny = window_size_x/cell_size_x;

const float update_delay = 0.05;




int main()
{


    // function prototype
    int neighbor_counter(int arg1, int arg2, unsigned int arg3[Nx][Ny]);


    srand(time(0));
    Clock clk;
    clk.restart();    // starting a clock


    // unsigned int random = rand() % 2;

    Font font;

    if (!font.loadFromFile("Fonts/arial.ttf")){
        std::cout << "Error loading font from file" << std::endl;
        system("pause");
    }


    std::stringstream oss;
    oss << 1;
    std::string str = "Generation = " + oss.str();



    Text text,text2;
    text.setFont(font);
    text.setString(str);
    text.setCharacterSize(12);
    text.setPosition(window_size_x - 150,window_size_y + 10);

    text2.setFont(font);
    text2.setString("Press Space to Start/Pause\nClick mouse while paused to toggle a cell\nPress Esc to quit");
    text2.setCharacterSize(12);
    text2.setPosition(5, window_size_y + offset_y + 1);




    RenderWindow window(VideoMode(window_size_x,window_size_y + window_extra_y), "Game of life");
    // window.clear(Color(216,27,29));
    window.clear(Color::Black);

    RectangleShape cell(Vector2f(cell_size_x,cell_size_y));
    // cell.setFillColor(Color(2,252,251));
    cell.setFillColor(live_cell);
    cell.setOutlineColor(Color(0,0,0));
    cell.setOutlineThickness(cell_border_thickness);




    unsigned int population_frame[Nx][Ny];
    unsigned int next_frame[Nx][Ny];

    for (int i = 0; i < Nx; i ++){
      for (int j = 0; j < Ny; j ++){
        population_frame[i][j] = rand() % 2;
      }
    }
    unsigned int generation = 1;

    bool wait = 1;

    while(window.isOpen())
    {


      Event e;




      while(window.pollEvent(e))
      {
        if (e.type == Event::Closed || e.key.code == Keyboard::Escape)
          window.close();

        if (e.type == Event::KeyPressed && e.key.code == Keyboard::Space)
          wait = !wait;

        if (wait == 1 && e.type == Event::MouseButtonPressed){
            int mouse_x = Mouse::getPosition(window).x;
            int mouse_y = Mouse::getPosition(window).y;

            int select_x = mouse_x / cell_size_x;
            int select_y = mouse_y / cell_size_y-1;  // troubleshooting required

            // std:: cout << mouse_y << "," << select_y << std:: endl;

            if (select_x < Nx & select_y  < Ny)
              population_frame[select_x][select_y] = !population_frame[select_x][select_y];



        }
      }





      // Calculate the next frame according to the rules (based on neighbor count)

      for (int i = 0; i < Nx; i ++){
        for (int j = 0; j < Ny; j ++){

          cell.setPosition(i*cell_size_x + offset_x, j*cell_size_y + offset_y);

          if (population_frame[i][j] == 1){
            cell.setFillColor(live_cell);
          } else{
            cell.setFillColor(dead_cell);
          }

          window.draw(cell);


          // count the number of neighbors

          int neighbor_n = 0;

          neighbor_n = neighbor_counter(i,j,population_frame);


          next_frame[i][j] = population_frame[i][j];

          if (population_frame[i][j] == 0){
              if (neighbor_n == 3)   next_frame[i][j] = 1;
          }


          if (population_frame[i][j] == 1){
              if ( (neighbor_n < 2) | (neighbor_n > 3))  next_frame[i][j] = 0;
          }




        }   // for j
      } // for i




      window.display();
      window.clear(Color::Black);
      window.draw(text);
      window.draw(text2);



      // Update
      // replace population_frame with next_frame

      if (clk.getElapsedTime().asSeconds() > update_delay && !wait)
      {
        unsigned int live_cells = 0;
        for (int i = 0; i < Nx; i ++){
          for (int j = 0; j < Ny; j ++){
            population_frame[i][j] = next_frame[i][j];
            live_cells = live_cells + next_frame[i][j];
          }
        }

        generation = generation + 1;
        oss.str("");
        oss << generation;
        str = "Generation = " + oss.str();

        oss.str("");
        oss << live_cells;
        str = str + "\nLive cells = " + oss.str();


        oss.str("");
        int temp = live_cells*10000/(Nx*Ny);
        float percent_live = temp/100.0;
        oss << percent_live;
        str = str + " (" + oss.str() + "%)";




        text.setString(str);
        // text.setPosition(10,window_size_y + 5);


        clk.restart();
      }



    }  // window.isOpen
    // std:: cout << generation;
    return 0;
}






// User defined functions


// Function for counting neighbors

int neighbor_counter(int ix,int jy, unsigned int population[Nx][Ny])
{
    int count = 0;

    for (int i = -1; i < 2; i ++){
      for (int j = -1; j < 2; j++ ){
        if (ix+i >= -1 && ix+i < Nx & jy+j >= -1 && jy+j < Ny ){
          count += population[ix+i][jy+j];
        }
      }
    }

    return count - population[ix][jy];

}
