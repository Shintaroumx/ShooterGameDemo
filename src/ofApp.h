#pragma once

#include "ofMain.h"

// 5.1.1 ������ 4 �����ռ�������
// p214 ������ǰ������
namespace CPPClass
{
	class MovingSprite;	
}

//  4.2.1 ��Ķ��� 
class ofApp : 
	// 7.2.1 ���м̳�
	public ofBaseApp
{	
	// -------- shared resource�� ������Դ ----------------//
	// �ؿ�����ɫ������ͼƬ
	ofImage ImgLevel;
	ofImage ImgPlayer;
	ofImage ImgBullet;
	ofImage ImgEnemy1;
	ofImage ImgEnemy2;
	// ����
	ofTrueTypeFont Font; 
	// ����
	ofSoundPlayer SoundBGMusic;
	// ��Ч
	ofSoundPlayer SoundBullet;
	ofSoundPlayer SoundLaugh;
	ofSoundPlayer SoundDie;
	ofSoundPlayer SoundMonsterDie;
	
	// ------------ ��Ϸ�еĸ��ֶ��� -----------------------//
	// level
	// �ؿ���Ϣ
	bool Running; // ����״̬
	float time; // ���ʱ��
	int score; // ����

	// player�����
	//4 �����ռ�������ķ��� ::
	//6.2.11 ����ָ��
	CPPClass::MovingSprite* Player;	
	ofVec2f Acc; // ��ҵļ��ٶ�
	
	// bullets	�ӵ�
	// 6.4 vector������10.3 ����
	// ����ָ��
	vector<CPPClass::MovingSprite*> Bullets;
	
	// enemy������
	// 6.4 vector����
	// ����ָ��
	vector<CPPClass::MovingSprite*> Enemys;	
	
	// ------------ methods ----------------------------------//
	public:
		// ��ʼ��
		void setup();

		// ����
		void update();

		// ��ʾ
		void draw();

		// ���̴���
		void keyPressed(int key);
		void keyReleased(int key);
		
		// ��괥��
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		// ���ڱ���
		void windowResized(int w, int h);
		
		// �ļ�����
		void dragEvent(ofDragInfo dragInfo);
		
		// ���յ�ofSendMessage()��������Ϣ
		void gotMessage(ofMessage msg);

		// -------------�������� ------------//
		// ��λ��Ϸ
		void resetGame();
		// eraseNullSprite ������������ɾ���Ѿ���NULL��ָ��
		// 3.1.3 -2 ���ô���
		void eraseNullSprite( vector<CPPClass::MovingSprite*>& S );
		// clearSprites ������������е���������
		// 3.1.3 -2 ���ô���
		void clearSprites( vector<CPPClass::MovingSprite*>& S );
		
		// ������ɵ���
		void randGenerateEnemy(  );
		// ����ж�
		void updatePlayer();
		// �����ж�		
		void updateEnemies( );
		// �ӵ��ж�
		void updateBullets();
		// ��������״̬
		void updateLifeStates();

		// ��ʾ����
		void drawLevel();

		// ��ҷ����ӵ���x,y
		void PlayerFireBulletTo( int x, int y );
		
		


		
};
