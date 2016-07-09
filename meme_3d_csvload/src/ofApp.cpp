#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofSetBackgroundAuto(false);
    ofBackground(0);

    ofSetCircleResolution(64);
    ofSetFrameRate(30);
    
    
    //dataフォルダに配置したcsvファイルの名前
    string filePath = "tamabi01.csv";
    loadCsvToMemes(filePath);
  
    //対象からの距離の初期値を指定
    cam.setDistance(300);
    focus = memes[index].zone_focus;
    next_focus = memes[index+1].zone_focus;
    calm = memes[index].zone_calm;
    next_calm = memes[index+1].zone_calm;
    posture = memes[index].zone_posture;
    next_posture = memes[index+1].zone_posture;
    }

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofBlendMode(ADD);
    
    morph_focus = ofLerp(focus,next_focus,percent);
    morph_calm = ofLerp(calm,next_calm,percent);
    morph_posture = ofLerp(posture,next_posture,percent);
    percent += 0.02;
    
    float background = 0;
    float basecolor = 100;
    float basealph = 50;
    float baser = 3;
    float margin = 100;
    step += 0.5;
    
    
    //string NAME
    ofSetColor(255);
    ofDrawBitmapString(memes[2].user_id, ofGetWidth()/2-25, ofGetHeight()/2);
    
    //string DATE
    ofSetColor(background);
    ofDrawCircle(10, step, 100);
    ofSetColor(255);
    ofDrawBitmapString(memes[index].zone_date, 10, step);
    
    //strinf focus//
    ofSetColor(background,50);
    ofDrawCircle(ofGetWidth()/2, step + 100,50);
    ofSetColor(morph_focus,basecolor,basecolor);
    ofDrawBitmapString(morph_focus, ofGetWidth()/2-20, step+100);
    
    //strinf calm//
    ofSetColor(background,50);
    ofDrawCircle(ofGetWidth()/2-margin, step + 100,50);
    ofSetColor(basecolor,morph_calm,basecolor);
    ofDrawBitmapString(morph_calm, ofGetWidth()/2-margin-20, step+100);

    //strinf posture//
    ofSetColor(background,50);
    ofDrawCircle(ofGetWidth()/2+margin, step + 100,50);
    ofSetColor(basecolor,basecolor,morph_posture);
    ofDrawBitmapString(morph_posture, ofGetWidth()/2+margin-20, step+100);
    
    
    
    //focus//
    ofSetColor(morph_focus,basecolor,basecolor,morph_focus + basealph);
    ofDrawCircle(ofGetWidth()/2,step,morph_focus/baser);
    
    //calm//
    ofSetColor(basecolor,morph_calm,basecolor, morph_calm + basealph);
    ofDrawCircle(ofGetWidth()/2-margin,step,morph_calm/baser);
    
    //posture//
    ofSetColor(basecolor,basecolor,morph_posture, morph_posture + basealph);
    ofDrawCircle(ofGetWidth()/2+margin,step,morph_posture/baser);
    
    
    
    //モーフィングの割合が1になった時の処理
    if (percent >=1.0) {
        //noLoop();
        //表示するデータのインデックスを進める
        index += 1;
        
        //配列の最後に到達したら停止
        if (index == memes.size() - 1) {
            //
        } else {
            //表示するデータと、次に表示するデータを更新
            focus = memes[index].zone_focus;
            next_focus = memes[index+1].zone_focus;
            
            calm = memes[index].zone_calm;
            next_calm = memes[index+1].zone_calm;
            
            posture = memes[index].zone_posture;
            next_posture = memes[index+1].zone_posture;
        }
        
        //モーフィングの割合を初期化
        percent = 0;
    }
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


