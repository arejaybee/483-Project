#include "SuperTicTacToe.h"
int main()
{
    SuperTicTacToe sttt;
    //int winners[4] = {0,0,0,0};
    /* for(int i = 0; i < 100; i++)
      {
	sttt.play();
	if(sttt.getAiWin() == -1)
	  {
	    winners[0]++;
	  }
	else if(sttt.getAiWin() == 0)
	  {
	    winners[1]++;
	  }
	else if(sttt.getAiWin() == 1)
	  {
	    winners[2]++;
	  }
	else
	  {
	    winners[3]++;
	  }
      }
      cout<<"The results are: "<<winners[0]<<" Wins for Rando\n"<<winners[1]<<"Tie games\n"<<winners[2]<<" Wins for AI\n"<<winners[3]<<" This should be 0"<<endl;*/
    sttt.play();
    return 0;
}
