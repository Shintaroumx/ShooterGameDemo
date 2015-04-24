// �����ظ��������ļ�
#pragma once 
// 5.6.4 ����Ԥ���� ��ֹͷ�ļ����ظ�����
#ifndef $SPRITE_H$
#define $SPRITE_H$

#include "ofMain.h"

// 5.1.1 ������ 4 �����ռ�������
namespace CPPClass
{
	// 4.2.1 ��Ķ��� 
	class MovingSprite
	{
	// 4.2.2 ���Ա�ķ��ʿ��ƣ�����
	public:
		// 4.3.1 ���캯��		
		MovingSprite(
			ofPoint Pos = ofPoint(0), // 3.3 Ĭ���β�
			ofVec2f Vel = ofVec2f(0,1), 
			ofVec2f Size=ofVec2f(20,20),  
			ofImage* I=NULL, // 6.2.11 ����ָ��
			int Score = 1);
		
		// 8.3.1 һ���麯����Ա
		// draw() ��ʾ
		virtual void draw();
		// update() ����
		virtual void update();
		// getScore() ��ֵ
		int getScore();
		
		// λ�õ����úͻ�ȡ
		void setPosition(ofPoint P);
		ofPoint getPosition();		
		ofRectangle getRect();// ������ڵľ��η�Χ
		
		// �ƶ�һ��λ�� Trans
		void move(ofVec2f Trans);	

		// �ٶȵı仯��
		void setVelocity(ofVec2f v);
		ofVec2f getVelocity();
		void accelerate(ofVec2f acc);
		void resist(float r = 0.99f);
	
		// getSize()/setSize() ���/���ó���ߴ�
		ofVec2f getSize();
		void setSize(ofVec2f s);
		// getImage()���������
		ofImage* getImage();
		
	// 4.2.2 ���Ա�ķ��ʿ��ƣ� ˽��
	private:
		// pos λ��
		ofPoint pos;
		// velocity �ٶ�
		ofVec2f velocity;
		// size ����ߴ�
		ofVec2f size;	
		// img ��ò
		// 6.2.11 ����ָ��
		ofImage* img;
		// score ��ֵ
		int score;
	};
}


#endif