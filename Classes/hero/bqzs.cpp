#include "bqzs.h"

bqzs::bqzs()
{
	name = "����ս��", skillname = "����", advice = "ǰ��";
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

void bqzs::upLevel(Hero* bqzs1)
{
	bqzs1->blood = 1080;//��ǰѪ��
	bqzs1->maxBlood = 1080;//����ֵ
	bqzs1->level = 2; //�ȼ�
	bqzs1->attack = 90; //������
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
	static Hero* enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
	static int attackNum = 0;
	auto lambda = [=](float dt) {
		this->update(this, enemy, dt);
		this->healthBar->setPercentage(((double)blood / (double)maxBlood) * 100);
		isDead();
	};
	this->schedule(lambda, 1 / 60.f, "bqzsMove");
	magicPro = magicpro;
	protect = pro;
	static double add = (level == 1) ? 40 : 65;
	static int hurt = (int)(enemy->attackRate * attack);
	auto lambdb = [=](float dt) {
		enemy = getEnemyByDistance(this, false, this->ofPlayer);//����
		if (enemy != nullptr &&state==ATTACK )
		{
			bqzs::bqzsnormalAttack(enemy, hurt, add);
			attackNum++;//�Ըõ��˵Ĺ�������+1
		}
	};
	this->schedule(lambdb, 1 / speed, "bqzsAttack");
	//�ͷż���
	if (blue == blueMax) {
		attackRate = 0.25;
		auto lambda = [=](float dt) {
			enemy->blood -= (int)(hurt - (enemy->protect) + add);
			//bqzs::swordswing(this);
		};
		this->scheduleOnce(lambda, 1 / speed * 2, "bqzsSkill");//���ٵ��ͷż���
		blue = 0;
		attackRate = 1;//�ָ�
	}
	if (enemy->blood < 0)
		enemy->blood = 0;//�з�����
	magicPro = magicpro;
	protect = pro;
}

void bqzs::bqzsnormalAttack(Hero* enemy, int hurt, double add)
{
	blue += 30;
	enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//���׵��������˺�
	if (enemy->blood < 0)
		enemy->blood = 0;
	swordwaive(this);
}

void bqzs::swordwaive(Hero* my)
{
	Sprite* sword = Sprite::create("./hero/sword.png");
	my->addChild(sword, 3);
	sword->setScale(2.0f);
	sword->setPosition(Vec2(600, 300));
	// ���赶�Ķ�������
	auto waive = Sequence::create(
		RotateTo::create(1.0f, 90),   // ��������ת
		RotateTo::create(1.0f, 0),      // ���ָ�ԭʼ�Ƕ�
		CallFunc::create([sword]() {
			sword->removeFromParent();
			}),
		nullptr
				);
	// ִ�ж�������
	sword->runAction(waive);
}

//void bqzs::swordswing(Hero* my)
//{
//	Sprite* sword = Sprite::create("./hero/sword.png");
//	my->addChild(sword, 3);
//	sword->setScale(2.0f);
//	sword->setPosition(Vec2(600, 300));
//
//	// ��ת���Ķ�������
//	auto swing = Sequence::create(
//		RotateTo::create(1.0f, 360),
//		CallFunc::create([sword]() {
//			sword->removeFromParent();
//			}),
//		nullptr
//				);
//	// ִ�ж�������
//	sword->runAction(swing);
//}