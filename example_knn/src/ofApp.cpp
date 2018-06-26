#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    knn.setK( 3 );

    bTrained = false;
    
    ofBackground( 0 );
    
    guess.x = -100;
    guess.y = -100;
    guess.z = 0;
    
    grid.allocate( ofGetWidth(), ofGetHeight() );
    grid.begin();
        ofClear( 0, 0, 0, 0);
    grid.end();

    ofSetWindowTitle( "knn classification study" );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){

    if( mode==1 && bTrained ){
        ofSetColor( 255 );
        grid.draw(0, 0);

        switch( int( guess.z ) ){
            case 0: ofSetColor(255, 0, 0 ); break;
            case 1: ofSetColor(0, 255, 0 ); break;
            case 2: ofSetColor(0, 0, 255 ); break;
            default: ofSetColor(255); break;
        }    
        ofDrawCircle( guess.x, guess.y, 12 );
    } 
    
    for( auto & example : examples ){
        switch( int(example.output[0]) ){
            case 0: ofSetColor(255, 0, 0 ); break;
            case 1: ofSetColor(0, 255, 0 ); break;
            case 2: ofSetColor(0, 0, 255 ); break;
            default: ofSetColor(255); break;
        }
        
        ofDrawCircle( example.input[0], example.input[1], 5 );
    }
    
    drawInfo();
}

//--------------------------------------------------------------
void ofApp::drawInfo(){
    ofSetColor( 255 );
    string info = "mode = ";
    if( mode == 0 ){ 
        info += "training\n";
        info += "click with different mouse buttons for example input\n";
        info += "backspace to clear all the examples\n";
        info += "K=";
        info += ofToString( knn.getK() );
        info += " press 1-5 to change\n";
        info += "spacebar to train model and run";
    } else {
        info += "run";
        if(bTrained) { 
            info+= " (training successful)\n"; 
            info += "click and drag to test input and output\n";    
        }else{
            info+= " (training failed)\n"; 
        }
        info += "K=";
        info += ofToString( knn.getK() );
        info += " press 1-5 to change\n";
        info += "spacebar to return to examples input";
    }
    ofDrawBitmapString( info, 20, 20 );
}

//--------------------------------------------------------------
void ofApp::train(){
    bTrained = knn.train( examples );
    if(bTrained){
        std::cout<<"training succesfull\n";
    }else{
        std::cout<<"training failed\n";
    }                        
    guess.x = -100;
    guess.y = -100;
    updateGrid();
}
//--------------------------------------------------------------
void ofApp::updateGrid(){
    grid.begin();
        ofClear(0, 0, 0, 0);
        if(bTrained){
            for( int x = 0; x<grid.getWidth(); x+=10 ){
                for (int y = 0; y<grid.getHeight(); y+=10){
                    std::vector<double> input = { double(x+5), double(y+5) };
                    int output =  knn.run( input )[0];

                    switch( output ){
                        case 0: ofSetColor( 80, 0, 0 ); break;
                        case 1: ofSetColor( 0, 80, 0 ); break;
                        case 2: ofSetColor( 0, 0, 80 ); break;
                        default: ofSetColor( 80 ); break;
                    }    
                    ofDrawLine( x, y+5, x+10, y+5);
                    ofDrawLine( x+5, y, x+5, y+10);
                }
            }            
        }
    grid.end();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if( mode==1 && bTrained ){
        guess.x = x;
        guess.y = y;
        std::vector<double> input = { double(x), double(y) };
        guess.z = knn.run( input )[0];
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    switch( mode ){
        case 0: // training
        {
            double dx = x;
            double dy = y;
            
            rapidlib::trainingExample example;
            example.input = { dx, dy };
            example.output = { double(button) };
            
            examples.push_back( example );
            
            std::cout<< "added point "<<dx<<" "<<dy<<" to class "<<button<<"\n";    
        }
        break;
        
        case 1: // run
        {
            if(bTrained){
                guess.x = x;
                guess.y = y;
                std::vector<double> input = { double(x), double(y) };
                guess.z = knn.run( input )[0];                
            }
        }
        break;
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
       
    switch( key ){
        case ' ':
            if (mode==0){ train(); }
            mode = mode ? 0 : 1; 
        break;
        
        case OF_KEY_BACKSPACE:
            if( mode==0 ){
                examples.clear();
            }
        break;
    }
    
    int K = key - '1' + 1;
    
    if(K>0 && K<=5){
        knn.setK(K);
        if(mode==1){
            train();
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

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
