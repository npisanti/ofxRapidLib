#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    network.setNumHiddenNodes( 3 );
    
    network.setNumHiddenLayers( 5 );
    
    bTrained = false;
    
    ofBackground( 0 );
    
    fbo.allocate( ofGetWidth(), ofGetHeight() );
    fbo.begin();
        ofClear( 0, 0, 0, 0);
    fbo.end();

    ofSetWindowTitle( "neural network regression" );
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofSetColor(255);
    for( auto & example : examples ){
        ofDrawCircle( example.input[0], example.output[0], 8 );
    }
    
    if( mode==1 && bTrained ){
        ofSetColor( 120 );
        fbo.draw(0, 0);
    }
    drawInfo();
}

//--------------------------------------------------------------
void ofApp::drawInfo(){
    ofSetColor( 255 );
    string info = "mode = ";
    if( mode == 0 ){ 
        info += "training\n";
        info += "click with mouse for example input\n";
        info += "spacebar to train model and run";
    } else {
        info += "run";
        if(bTrained) { 
            info+= " (training successful)\n"; 
            info += "click and drag to test input and output\n";    
        }else{
            info+= " (training failed)\n"; 
        }
        info += "spacebar to return to examples input";
    }
    ofDrawBitmapString( info, 20, 20 );
}

//--------------------------------------------------------------
void ofApp::train(){
    bTrained = network.train( examples );
    if(bTrained){
        std::cout<<"training succesfull\n";
    }else{
        std::cout<<"training failed\n";
    }                        

    updateCurve();
}
//--------------------------------------------------------------
void ofApp::updateCurve(){
    fbo.begin();
        ofClear(0, 0, 0, 0);
        
        if(bTrained){
            for( int x=2; x<fbo.getWidth(); x+=4 ){
                std::vector<double> input = { double(x) };  
                float y = network.run( input )[0];
                ofDrawCircle( x, y, 2 );
            }
        }
    fbo.end();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    if( mode==1 && bTrained ){

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
            example.input = { double(dx) };
            example.output = { double(dy) };
            
            examples.push_back( example );
            
            std::cout<< "mapped value "<<dx<<" to output "<<dy<<"\n";    
        }
        break;
        
        case 1: // run
        {
            if(bTrained){
             
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
