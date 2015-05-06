#include "ofApp.h"
#include "MovingSprite.h"
#include "HuntingSprite.h"

using namespace  CPPClass;

//--------------------------------------------------------------
void ofApp::setup(){
	// ����֡��Ϊ30
	ofSetFrameRate(30);
		
	// ��ȡ��Դ�ļ�
	ImgLevel.loadImage("Level.jpg");
	ImgPlayer.loadImage("Player.png");
	ImgBullet.loadImage("Bullet.png");
	ImgEnemy1.loadImage("Enemy1.png");
	ImgEnemy2.loadImage("Enemy2.png");	
	Font.loadFont("vag.ttf",25);
	SoundBGMusic.loadSound("background.mp3");
	SoundBGMusic.setLoop(true);
	SoundBGMusic.setVolume(0.5f);
	SoundBGMusic.play();
	SoundBullet.loadSound("bullet.mp3");
	SoundBullet.setVolume(0.5f);
	SoundBullet.setLoop(false);
	SoundBullet.setMultiPlay(true);
	SoundLaugh.loadSound("laughSordid.mp3");
	SoundLaugh.setVolume(1.0f);
	SoundLaugh.setLoop(false);
	SoundLaugh.setMultiPlay(false);
	SoundDie.loadSound("die.mp3");
	SoundDie.setVolume(1.0f);
	SoundDie.setLoop(false);
	SoundDie.setMultiPlay(true);	
	SoundMonsterDie.loadSound("monsterDie.mp3");
	SoundMonsterDie.setVolume(0.7f);
	SoundMonsterDie.setLoop(false);
	SoundMonsterDie.setMultiPlay(true);

	// ��λ��Ϸ
	Player = NULL;
	resetGame();
}

//--------------------------------------------------------------
void ofApp::update(){
	
	
	// �����������״̬���������������
	if(Running)
	{			
		// �����ӵ���
		randGenerateEnemy();

		// ����ж�
		updatePlayer();		

		// �ӵ��ж�
		updateBullets();

		// �����ж�
		updateEnemies();

		// �����ж�
		updateLifeStates();

		// ��ʱ
		time += ofGetLastFrameTime();
	}	

	// ɾ���ӵ����к͵��������еĿ�ָ��
	eraseNullSprite(Bullets);
	eraseNullSprite(Enemys);
}

//--------------------------------------------------------------
void ofApp::draw(){
	
	// ɾ���ӵ����к͵��������еĿ�ָ��
	eraseNullSprite(Bullets);
	eraseNullSprite(Enemys);

	// ��ʾ����
	drawLevel();

	// ��ʾ����MovingSprite
	if(Running)
	{
		Player->draw();
		
		int numB = Bullets.size();
		for(int i=0;i<numB;i++)
		{
			Bullets[i]->draw();
		}
		int numE = Enemys.size();
		for(int i=0;i<numE;i++)
		{
			Enemys[i]->draw();
		}
	}	

	// ��ʾ������ʱ��
	string Score = "score:" + ofToString(score);
	string Time = "Time:" + ofToString(int(time*100)/100.0f);
	Font.drawString(Score,20,35);
	Font.drawString(Time,ofGetWidth()-200,35);

	
	if(!Running)
	{
		// ofPushMatrix()/ofPopMatrix():
		//��ͼ�α仯�����ڶ���֮��
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2,ofGetHeight()/2);
		float scl = 2.0f + 0.4f*sin(5.0f*ofGetElapsedTimef());
		ofScale(scl,scl,1.0f);
		// ofPushStyle()/ofPopStyle():
		//�����Ʒ�񣨱�����ɫ�����Ƶ�����֮��
		ofPushStyle();
		ofSetColor(ofColor::red);
		Font.drawString("YOU'RE DEAD!", 
			-100,0);
		ofPopStyle();
		ofPopMatrix();

		Font.drawString("F1: restart", 20,ofGetHeight()-35);
	}
	
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

	// wasd ������ҵļ��ٶ�
	float A = 1.0f;	
	if('w'==key)
	{
		Acc = ofVec2f(0,-A);
	}
	else if(key=='s')
	{
		Acc = ofVec2f(0,A);
	}
	else if('a'==key)
	{
		Acc = ofVec2f(-A,0);
	}
	else if('d' ==key)
	{
		Acc = ofVec2f(A,0);
	}
	// ��f1��λ
	else if(OF_KEY_F1==key)
	{
		resetGame();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// wasd���ⰴ���ͷź󣬼��ٶ�Ϊ0
	if('w'==key||'s'==key||'a'==key||'d'==key)
	{
		Acc = ofVec2f(0,0);
	}
	
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	PlayerFireBulletTo(x, y);
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

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

// ע����������ã�����ԭ��
void ofApp::eraseNullSprite( vector<CPPClass::MovingSprite*>& S )
{
	if(S.size()==0)
	{
		return;
	}
	int num = S.size();
	for(int i=num-1;i>=0;i--)
	{
		if(S[i]==NULL)
		{
			S.erase(S.begin()+i);
		}
	}
}

// ע����������ã�����ԭ��
void ofApp::clearSprites( vector<CPPClass::MovingSprite*>& S )
{
	int num = S.size();
	for(int i=0;i<num;i++)
	{
		delete S[i];
		S[i]=NULL;
	}
	for(int i=0;i<num;i++)
	{
		S.erase(S.begin());
	}
}

void ofApp::resetGame()
{
	Running = true;
	time = 0;
	score = 0;

	if(Player!=NULL)
	{
		delete Player;
	}
	// 6.3 ��̬�ڴ����
	Player = new MovingSprite(
		ofPoint(ofGetWidth()/2,ofGetHeight()-20),
		ofVec2f(0),
		ofVec2f(30,30),		
		&ImgPlayer);

	Acc = ofVec2f(0,0);
	clearSprites(Bullets);
	clearSprites(Enemys);
}

void ofApp::randGenerateEnemy(  )
{
	// ���������
	float rn = ofRandom(0,100);
	// ����ָ���������ﵽĿ�ģ�ʱ��Խ�ã�
	// ���ɵ��˵ĸ���ProbabilityֵԽ��
	float Probability = 1.0f - exp(-0.01f*time);
	Probability *= 20.0f;
	if(rn<Probability) // �����С�� Probability, ���ɵ���
	{
		// ��0.8�������ɱ������ˣ���0.2�������ɸ��ٵ���
		int rn2 = ofRandom(0,100);
		MovingSprite* enemy;
		if(rn2<80)
		{
			// 6.3 ��̬�ڴ����
			enemy = new MovingSprite(
				ofPoint(ofRandom(1,ofGetWidth()-1),1),
				ofVec2f(ofRandom(-1,1),ofRandom(3,5)),
				ofVec2f(ofRandom(25,35),ofRandom(25,35)),					
				&ImgEnemy1);
		}
		else
		{
			// 6.3 ��̬�ڴ����
			enemy = new HuntingSprite(Player,
				ofPoint(ofRandom(1,ofGetWidth()-1),1),
				ofVec2f(ofRandom(-1,1),ofRandom(3,5)),
				ofVec2f(ofRandom(15,25),ofRandom(15,25)),					
				1.0f,
				&ImgEnemy2);
			// ��Ц
			SoundLaugh.play();
		}

		Enemys.push_back(enemy);
	}
}

void ofApp::updateEnemies()
{
	// RLevel ����
	ofRectangle RLevel(0,0,ofGetWidth(),ofGetHeight());
	// RectPlayer ������ڵľ���
	ofRectangle RectPlayer = Player->getRect();

	// �������е��ˣ�ִ���Լ����ж�
	int numE = Enemys.size();
	for(int i=0;i<numE;i++)
	{
		// ����
		Enemys[i]->update();			
	}
}

void ofApp::updateBullets()
{
	// ����ÿ���ӵ����ƶ�
	int numB = Bullets.size();
	for(int i=0;i<numB;i++)
	{
		if(Bullets[i]==NULL)
		{
			continue;
		}
		// �ӵ��
		Bullets[i]->update();
		// �ӵ�����
		Bullets[i]->resist(0.98);
	}
}

void ofApp::updatePlayer()
{	
	// ��Ҹı��ٶ�
	Player->accelerate(Acc);
	// ��һ
	Player->update();
	// ��Ҽ���
	Player->resist(0.9);	
}

void ofApp::drawLevel()
{
	float w,h;
	w = ofGetWidth();
	h = ofGetHeight();
	ImgLevel.draw(0,0,w,h);
}

void ofApp::PlayerFireBulletTo( int x, int y )
{
	//�ӵ���ʼλ��Ϊ���λ��
	ofPoint PosPlayer = Player->getPosition();

	// �ӵ����Ŀ��Ϊ���λ��
	ofPoint MousePos(x,y);

	// �ӵ�����ΪĿ��λ�ü�ȥ�ӵ���ʼλ��
	ofVec2f Dir = MousePos-PosPlayer;
	Dir.normalize();
	
	// �ӵ������Ϊ�䷽��ʸ����15��
	ofVec2f VelBullet = Dir*15.0f;

	// �ӵ������ٶ�=�����ٶ�+����ٶ�
	ofVec2f FireVel = VelBullet + Player->getVelocity();

	// �����ӵ�
	MovingSprite* bullet = 
		new MovingSprite(
		ofPoint(PosPlayer),
		FireVel,
		ofVec2f(10,10),
		&ImgBullet);
	Bullets.push_back(bullet);

	// ����
	SoundBullet.play();
}

void ofApp::updateLifeStates()
{
	//����������ж�1���������߽磬��Ϸ����
	ofRectangle RectPlayer = Player->getRect();
	ofRectangle RLevel(0,0,ofGetWidth(),ofGetHeight());
	if(!RectPlayer.intersects(RLevel))
	{			
		Running = false;
		// �ҽ�
		SoundDie.play();		
	}
	//����������ж�2�������˴���
	int numE = Enemys.size();
	for(int i=0;i<numE;i++)
	{
		ofRectangle RectEnemy = Enemys[i]->getRect();
		// �Ƿ�ץס���
		if(RectPlayer.intersects(RectEnemy))
		{
				// ��Ϸ����
				Running = false;
				// �ҽ�
				SoundDie.play();
		}					
	}

	// ���˺��ӵ��������ж�
	numE = Enemys.size();
	// �Ƿ����
	for(int i=0;i<numE;i++)
	{
		ofPoint P = Enemys[i]->getPosition();
		if(!RLevel.inside(P))
		{
			delete Enemys[i];// 6.3 ��̬�ڴ����
			Enemys[i] =NULL;
			continue;
		}	
	}
	eraseNullSprite(Enemys);

	//���Ƿ��ӵ�
	numE = Enemys.size();
	for(int i=0;i<Enemys.size();i++)
	{			
			ofRectangle RectEnemy = Enemys[i]->getRect();	
			int numB = Bullets.size();
			for(int j=0;j<numB;j++)
			{
				if(Bullets[j]==NULL)
				{
					continue;
				}
				ofPoint PBullet = Bullets[j]->getPosition();
				if(RectEnemy.inside(PBullet)&&Enemys[i]!=NULL)// �е�
				{
					// ɾ�����˺��ӵ�
					score += Enemys[i]->getScore();
					delete Enemys[i]; // 6.3 ��̬�ڴ����
					Enemys[i] =NULL;
					Bullets[j]->setVelocity(ofVec2f(0));					

					// ������Ч
					// �Բ�ͬ�Ĵ�С���ٶȲ��ţ�ʵ��ÿ�����ﲻͬ����
					SoundMonsterDie.setVolume(ofRandom(0.4f,0.8f));
					SoundMonsterDie.setSpeed(ofRandom(0.5f,1.5f));
					SoundMonsterDie.play();
				}
			}			
	}		
	eraseNullSprite(Enemys);	

	// �ӵ������ж�
	int numB = Bullets.size();
	for(int i=0;i<numB;i++)
	{
		if(Bullets[i]==NULL)
		{
			continue;
		}
		
		if(Bullets[i]->getVelocity().length()<0.33f)
		{
			// �ӵ��ٶȹ�С������ʧ
			delete Bullets[i];
			Bullets[i]=NULL;
		}
	}
	eraseNullSprite(Bullets);

	

}
