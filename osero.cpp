#include "DxLib.h"

void syoki_rtn();
void sente_rtn();
void gote_rtn();
void hantei_rtn();

int i, j, x, y, player;
int maisu0, maisu1;
int goban[10][10];

int WINAPI WinMain(HINSTANCE hI, HINSTANCE hP, LPSTR lpC, int nC){
  ChangeWindowMode(TRUE); //FALSEにすると、画面いっぱいの実行になる
  if(DxLib_Init() == -1) return -1;
  
  syoki_rtn();
  
  while(1){
    if(player == 0)
      sente_rtn();
    else
      gote_rtn();
      
    maisu0 = maisu1 = 0;
    for(i=1; i<9; i++)
      for(j=1; j<9; j++)
        if(goban[i][j]==0) maisu0++;
        if(goban[i][j]==1) maisu1++;
    
    if(maisu0+maisu1 > 63)
      break;
    else
      player = ++player%2;
  }
  
  if(maisu0>maisu1)
    DrawString(470, 450, "先手の勝ち！", 0xFF0000);
  else
    DrawString(470, 450, "後手の勝ち！", 0xFF0000);
    
  WaitKey();
  DxLib_End();
  return 0;
}



void syoki_rtn(){
  for(i=0; i<10; i++)
    for(j=0; j<10; j++)
      goban[i][j] = 3;
  
  for(i=1; i<9; i++)
    for(j=0; j<9; j++)
      goban[i][j] = 2;
      
  DrawBox(0, 0, 640, 480, 0xFFAAAA, TRUE); //ピンクで背景塗りつぶし
  
  DrawString(230, 10, "オセロ", 0x0000FF); //青
  
  DrawString(470, 50, "先手", 0x0000FF);
  DrawCircle(530, 60, 15, 0x000000, TRUE); //黒、丸の塗りつぶし
  DrawString(470, 100, "後手", 0x0000FF);
  DrawCircle(530, 110, 15, 0xFFFFFF, TRUE); //白、丸の塗りつぶし
  DrawCircle(530, 110, 15, 0x000000, FALSE); //黒、丸の枠
  
  DrawString(470, 150, "上へ　↑", 0x0000FF);
  DrawString(470, 200, "下へ　↓", 0x0000FF);
  DrawString(470, 250, "左へ　←", 0x0000FF);
  DrawString(470, 300, "右へ　→", 0x0000FF);
  DrawString(470, 350, "パス　Ctrl（右側）", 0x0000FF);
  DrawString(470, 400, "決定　Enter", 0x0000FF);
  
  goban[5][4] = 0;
  DrawCircle(5*50+25, 4*50+25, 20, 0x000000, TRUE);
  goban[4][5] = 0;
  DrawCircle(4*50+25, 5*50+25, 20, 0x000000, TRUE);
  
  goban[4][4] = 1;
  DrawCircle(4*50+25, 4*50+25, 20, 0xFFFFFF, TRUE);
  DrawCircle(4*50+25, 4*50+25, 20, 0x000000, FALSE);
  goban[5][5] = 1;
  DrawCircle(5*50+25, 5*50+25, 20, 0xFFFFFF, TRUE);
  DrawCircle(5*50+25, 5*50+25, 20, 0x000000, FALSE);
  
  for(x=1; x<9; x++)
    for(y=1; y<9; y++)
      DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE);
      
  x=y=1;
  player = 0;
}



void sente_rtn(){
  while(1){
    DrawBox(x*50, y*50, x*50+50, y*50+50, 0x000000);
    WaitKey();
    
    if(CheckHitKey(KEY_INPUT_UP)==1)
      if(y>1){
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE); //緑でその場所を消して、
        --y;
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x000000, FALSE); //黒枠で次の場所を示す
      }
    if(CheckHitKey(KEY_INPUT_DOWN)==1)
      if(y<8){
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE); //緑でその場所を消して、
        ++y;
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x000000, FALSE); //黒枠で次の場所を示す
      }
    if(CheckHitKey(KEY_INPUT_LEFT)==1)
      if(x>1){
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE); //緑でその場所を消して、
        --x;
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x000000, FALSE); //黒枠で次の場所を示す
      }
    if(CheckHitKey(KEY_INPUT_RIGHT)==1)
      if(x<8){
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE); //緑でその場所を消して、
        ++x;
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x000000, FALSE); //黒枠で次の場所を示す
      }
    if(CheckHitKey(KEY_INPUT_RCONTROL)==1) return;
    if(CheckHitKey(KEY_INPUT_RETURN)==1){
      if(goban[x][y]==2){
        goban[x][y]=0;
        DrawCircle(x*50+25, y*50+25, 20, 0x000000, TRUE);
        hantei_rtn();
      }else{
        DrawString(470, 450, "エラー", 0xFF0000);
        WaitTimer(1200);
        DrawString(470, 450, "エラー", 0xFF0000);
      }
      break;
    }
  }
}


void gote_rtn(){
  while(1){
    DrawBox(x*50, y*50, x*50+50, y*50+50, 0xFFFFFF, FALSE);
    WaitKey();
    
    if(CheckHitKey(KEY_INPUT_UP)==1)
      if(y>1){
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE); //緑でその場所を消して、
        --y;
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0xFFFFFF, FALSE); //黒枠で次の場所を示す
      }
    if(CheckHitKey(KEY_INPUT_DOWN)==1)
      if(y<8){
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE); //緑でその場所を消して、
        ++y;
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0xFFFFFF, FALSE); //黒枠で次の場所を示す
      }
    if(CheckHitKey(KEY_INPUT_LEFT)==1)
      if(x>1){
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE); //緑でその場所を消して、
        --x;
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0xFFFFFF, FALSE); //黒枠で次の場所を示す
      }
    if(CheckHitKey(KEY_INPUT_RIGHT)==1)
      if(x<8){
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0x00FF00, FALSE); //緑でその場所を消して、
        ++x;
        DrawBox(x*50, y*50, x*50+50, y*50+50, 0xFFFFFF, FALSE); //黒枠で次の場所を示す
      }
    if(CheckHitKey(KEY_INPUT_RCONTROL)==1) return;
    if(CheckHitKey(KEY_INPUT_RETURN)==1){
      if(goban[x][y]==2){
        goban[x][y]=1;
        DrawCircle(x*50+25, y*50+25, 20, 0xFFFFFF, TRUE);
        DrawCircle(x*50+25, y*50+25, 20, 0x000000, FALSE);
        hantei_rtn();
      }else{
        DrawString(470, 450, "エラー", 0xFF0000);
        WaitTimer(1200);
        DrawString(470, 450, "エラー", 0xFF0000);
      }
      break;
    }
  }
}




void hantei_rtn(){
  int k, sw=0;
  
  if(player==0){
    for(k=1; goban[x-k][y]==1; k++);
    if(k>1 && goban[x-k][y]==0){
      sw=1;
      for(k--; k>0; k--){
        goban[x-k][y] = 0;
        DrawCircle((x-k)*50+25, y*50+25, 20, 0x000000, TRUE);
      }
    }
    
    for(k=1; goban[x+k][y]==1; k++);
    if(k>1 && goban[x+k][y]==0){
      sw=1;
      for(k--; k>0; k--){
        goban[x+k][y] = 0;
        DrawCircle((x+k)*50+25, y*50+25, 20, 0x000000, TRUE);
      }
    }
    
    for(k=1; goban[x][y-k]==1; k++);
    if(k>1 && goban[x][y-k]==0){
      sw=1;
      for(k--; k>0; k--){
        goban[x][y-k] = 0;
        DrawCircle(x*50+25, (y-k)*50+25, 20, 0x000000, TRUE);
      }
    }
    
    for(k=1; goban[x][y+k]==1; k++);
    if(k>1 && goban[x][y+k]==0){
      sw=1;
      for(k--; k>0; k--){
        goban[x][y+k] = 0;
        DrawCircle(x*50+25, (y+k)*50+25, 20, 0x000000, TRUE);
      }
    }
    
    for(k=1; goban[x-k][y-k]==1; k++);
    if(k>1 && goban[x-k][y-k]==0){
      sw=1;
      for(k--; k>0; k--){
        goban[x-k][y-k] = 0;
        DrawCircle((x-k)*50+25, (y-k)*50+25, 20, 0x000000, TRUE);
      }
    }
    
    for(k=1; goban[x+k][y+k]==1; k++);
    if(k>1 && goban[x+k][y+k]==0){
      sw=1;
      for(k--; k>0; k--){
        goban[x+k][y+k] = 0;
        DrawCircle((x+k)*50+25, (y+k)*50+25, 20, 0x000000, TRUE);
      }
    }
    
    for(k=1; goban[x-k][y+k]==1; k++);
    if(k>1 && goban[x-k][y+k]==0){
      sw=1;
      for(k--; k>0; k--){
        goban[x-k][y+k] = 0;
        DrawCircle((x-k)*50+25, (y+k)*50+25, 20, 0x000000, TRUE);
      }
    }
    
    for(k=1; goban[x+k][y-k]==1; k++);
    if(k>1 && goban[x+k][y-k]==0){
      sw=1;
      for(k--; k>0; k--){
        goban[x+k][y-k] = 0;
        DrawCircle((x+k)*50+25, (y-k)*50+25, 20, 0x000000, TRUE);
      }
    }
  }else{
    //白番
  }
}
