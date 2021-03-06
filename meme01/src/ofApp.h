#pragma once

#include "ofMain.h"

struct Meme {
    //memeから取得したデータ各種を格納するクラス
    string user_id;
    string zone_date;
    float zone_focus;
    float zone_calm;
    float zone_posture;
};


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int index = 0;
    float focus;        //表示するデータ
    float next_focus;
    float morph_focus;  //データ間をモーフィングしたデータ
    
    float calm;
    float next_calm;
    float morph_calm;
    
    float posture;
    float next_posture;
    float morph_posture;
    
    float percent = 0;
    float step =0;
    
    
    // 指定されたcsvを読み込んで、Memesの配列を作る関数
    void loadCsvToMemes(string filePath);
    
    //Memeのデータを格納するmemes配列
    vector<Meme> memes;
    
    //各データの最大最小を格納する変数
    float max_focus, min_focus;
    float max_calm, min_calm;
    float max_posture, min_posture;
    
    //ProcessingのPeasyCamとほぼ同じ、ofEasyCamオブジェクト
    ofEasyCam cam;
    
};
