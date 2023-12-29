#include "bqzs.h"

bqzs::bqzs()
{
	name = "����ս��", skillname = "����";
	skillType = PHYSICS;//̹��
	blood = 600;
	maxBlood = 600;//Ѫ��
	level = 1; //�ȼ�
	attack = 50; //������
	protect = 40;//����
	magicPro = 20;//ħ��
	state = 1;//����״̬
	price = 1;//����
	speed = 0.6;//����
}

void bqzs::upLevelbqzs(Hero* bqzs1, Hero* bqzs2, Hero* bqzs3)
{
	bqzs1->blood = 1080;//��ǰѪ��
	bqzs1->maxBlood = 1080;//����ֵ
	bqzs1->level = 2; //�ȼ�
	bqzs1->attack = 90; //������
	bqzs2->removeFromParent();
	bqzs3->removeFromParent();
}


Hero* bqzs::initbqzs()
{
	Hero* bqzs = static_cast<Hero*>(bqzs::create());
	//my = bqzs;
	bqzs->picturename = "./hero/bqzs.png";
	bqzs->picturenum = 1;
	bqzs->heroAnimation(bqzs->picturename, bqzs->picturenum, bqzs,speed, -1);
	//tfns->autorelease();
	return bqzs;
}


void bqzs::Play()
{
	
	
	int magicpro = magicPro;
	int pro = protect;
	
	//while (!isDead() && !isWin(&myPlayerData, &opPlayerData)) {
	static Hero* enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
	static int attackNum = 0;
	auto lambda = [=](float dt) {
		this->update(this, enemy, dt);
	};
	this->schedule(lambda, 1 / 60.f, "bqzsMove");
		magicPro = magicpro;
		protect = pro;
		attackNum = 0;
		static double add = (level == 1) ? 40 : 65;
		static int hurt = (int)(enemy->attackRate * attack);
		//while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK) {
			attackNum++;//�Ըõ��˵Ĺ�������+1
			auto lambdb = [=](float dt) {
				bqzs::bqzsnormalAttack(enemy,hurt,add);
			};
			this->schedule(lambdb, 1 / speed, "bqzsAttack");
			auto lambdc = [=](float dt) {
				enemy->setColor(Color3B::RED);
			};
			this->schedule(lambdc, speed, "tmp");
			//�ͷż���
			if (blue == blueMax) {
				int i = 0;
				while (i < 9) {
					attackRate = 0.25;
					auto lambda = [=](float dt) {
						enemy->blood -= (int)(hurt - (enemy->protect) + add);
						//bqzs::swordswing("",this);//??????????//picture
					};
					this->schedule(lambda, 1 / speed * 2,"bqzsSkill");//���ٵ��ͷż���
					//�ͷż���ʱ����˱�ɳ�ɫ
					auto lambdc = [=](float dt) {
						enemy->setColor(Color3B::BLACK);
					};
					this->schedule(lambdc, 1/speed*2, "tmp11");
					i++;
				}
				blue = 0;
				attackRate = 1;//�ָ�
			}
			if (enemy->blood < 0)
				enemy->blood = 0;//�з�����
		//}
	magicPro = magicpro;
	protect = pro;
	//}
	//this->removeFromParent();
}

void bqzs::bqzsnormalAttack(Hero* enemy,int hurt, double add)
{
	blue += 30;
	enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt- enemy->protect;//���׵��������˺�
	enemy->setColor(Color3B::ORANGE);
	//swordwaive("sword.png",this);//??????????//picture
}

//void bqzs::swordwaive(string picturename, Hero* my)
//{
//	Sprite* sword = Sprite::create(picturename);
//	this->addChild(sword);
//	sword->setPosition(Vec2(0, 0)); // ���õ��ĳ�ʼλ��//??????????//���ľ��룿
//
//	// ���赶�Ķ�������
//	auto waive = Sequence::create(
//		RotateTo::create(0.05f, -45),   // ��������ת
//		RotateTo::create(0.1f, 0),      // ���ָ�ԭʼ�Ƕ�
//		nullptr
//	);
//	// ִ�ж�������
//	sword->runAction(waive);
//}
//
//void bqzs::swordswing(string picturename, Hero* my)
//{
//	Sprite* sword = Sprite::create(picturename);
//	this->addChild(sword);
//	sword->setPosition(Vec2(0, 0)); // ���õ��ĳ�ʼλ��//??????????//���ľ��룿
//
//	// ��ת���Ķ�������
//	auto swing = Sequence::create(
//		RotateTo::create(0.1f, 360),   // ����ת//??????????//����time��
//		nullptr
//	);
//	// ִ�ж�������
//	sword->runAction(swing);
//}