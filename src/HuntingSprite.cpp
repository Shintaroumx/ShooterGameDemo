#include "HuntingSprite.h"

// 5.1.1 ������ 4 �����ռ�������
// p21 using namespace
using namespace CPPClass; 

//p117 ����๹�캯�������һ����ʽ
CPPClass::HuntingSprite::HuntingSprite( 
	MovingSprite* Target, 
	ofPoint Pos /*= ofPoint(0)*/, 
	ofVec2f Vel /*= ofVec2f(0,1)*/,
	ofVec2f Size/*=ofVec2f(20,20)*/,
	float Agility /*= 1.0f*/, 
	ofImage* I/*=NULL*/,
	int Score /*= 2*/ ) :
	MovingSprite(Pos,Vel,Size,I,Score),
	target(Target),
	agility(Agility)
{}

void CPPClass::HuntingSprite::update()
{
	if(target!=NULL)
	{		
		// ���ٶȲ����仯���ٶ�����Ŀ��ƫת		
		turnToTarget();
	}
	// 7.5.1������ֱ��:: �������ڷ��ʻ���ĺ���update()
	MovingSprite::update();
}

void CPPClass::HuntingSprite::turnToTarget()
{
	// 6.2.11-1 ->�����
	ofPoint PTarget = target->getPosition();
	ofPoint PSelf = getPosition();

	ofVec2f IToTarget = PTarget-PSelf; // IToTarget����this��Ŀ���ʸ��
	// ��һ��Ϊ����this��Ŀ��ĵ�λʸ��
	IToTarget.normalize(); 
	// V: �ٶ�ʸ��
	ofVec2f V = getVelocity(); 
	// VNorm: �ٶȵĵ�λʸ��
	ofVec2f VNorm = V.normalized(); 
	//DVel�� �ٶȵĸı����� ������agility��ʸ��(IToTarget - VNorm)
	ofVec2f DVel = 0.5f*agility*(IToTarget - VNorm); 
	// �ٶȱ仯
	V += DVel;
	setVelocity(V);
}
