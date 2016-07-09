#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    
    //dataフォルダに配置したcsvファイルの名前
    string filePath = "tamabi01.csv";
    loadCsvToMemes(filePath);
    
    
    ofEnableDepthTest();
    //対象からの距離の初期値を指定
    cam.setDistance(300);

    
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    cam.begin();
    
    ofBackground(0);
    
    float dim = 2;
    
    for(int i=0; i< memes.size(); i++){
    
        Meme meme = memes[i];
        
        //map関数でデータを高さに適した値に変換
        float boxHeight = ofMap(meme.zone_focus, min_focus, max_focus, 0.1, 50);
        
        //map関数でデータをX座標に適した値に変換
        float posX = ofMap(meme.zone_calm, min_calm, max_calm, -100, 100);
        
        //map関数でデータをZ座標に適した値に変換
        float posZ = ofMap(meme.zone_posture, min_posture, max_posture, -100, 100);
        
        //map関数でデータを色さに適した値に変換
        float boxColorR = ofMap(meme.zone_calm, min_calm, max_calm, 64, 255);
        float boxColorG = ofMap(meme.zone_posture, min_posture, max_posture, 64, 255);
        
        ofSetColor(boxColorR, boxColorG, 255, 128);
        
        //ofDrawBoxでbarchartを描く
        //ofDrawBox(x,y,z,w,h,d)
        //x,y,zはboxの中心の座標です。
        ofDrawBox(posX, boxHeight/2, posZ, dim, boxHeight, dim);
        
        
    }
    
    //XZ平面のグリッドを描く
    ofSetColor(64);
    int minGrid = -150;
    int maxGrid = 150;
    int gridMargin = 10;
    for(int i=minGrid; i<=maxGrid; i+=gridMargin){
        if(i==0) {
            ofSetLineWidth(1);
        }
        else{
            ofSetLineWidth(0.25);
        }
        
        ofDrawLine(i,0,minGrid,i,0,maxGrid);
        ofDrawLine(minGrid,0,i,maxGrid,0,i);
    }
    
    
    cam.end();
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void ofApp::loadCsvToMemes(string filePath){
    ofFile file(filePath);
    
    if(!file.exists()){
        ofLogError("The file " + filePath + " is missing");
    }
    
    ofBuffer buffer(file);
    
    //データをVector(配列)に読み込む
    //CSVファイルを読み込んで、1行ごとに配列linesの要素として読み込む
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        vector<string> data = ofSplitString(line, ",");
        if (data.size()>=6) {
            
            Meme meme;
            meme.user_id = data[0];
            meme.zone_date = data[1];
            meme.zone_focus = ofToFloat(data[3]);
            meme.zone_calm = ofToFloat(data[4]);
            meme.zone_posture = ofToFloat(data[5]);
            memes.push_back(meme);
            
            if(it == buffer.getLines().begin()){
                max_focus = min_focus = meme.zone_focus;
                max_calm = min_calm = meme.zone_calm;
                max_posture  = min_posture = meme.zone_posture;
            }
            else{
                //データをひとつずつ比較しながら最小値最大値を調べる
                max_focus = (meme.zone_focus > max_focus) ? meme.zone_focus : max_focus;
                min_focus = (meme.zone_focus < min_focus) ? meme.zone_focus : min_focus;
                max_calm = (meme.zone_calm > max_calm) ? meme.zone_calm : max_calm;
                min_calm = (meme.zone_calm < min_calm) ? meme.zone_calm : min_calm;
                max_posture = (meme.zone_posture > max_posture) ? meme.zone_posture : max_posture;
                min_posture = (meme.zone_posture < min_posture) ? meme.zone_posture : min_posture;
                
            }
            
        }
    }
}


