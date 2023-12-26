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
	magic = 100;
	state = 1;//����״̬
	price = 1;//����
	x = 0, y = 0;//�������ϵ�����
	speed = 0.6;//����
}


Hero* bqzs::initbqzs()
{
	Hero* bqzs = static_cast<Hero*>(bqzs::create());
	my = bqzs;
	bqzs->picturename = "./hero/bqzs%d.png";
	bqzs->picturenum = 3;
	bqzs->heroAnimation(bqzs->picturename, bqzs->picturenum, bqzs, bqzs->getPosition(), speed, -1);
	//tfns->autorelease();
	return bqzs;
}


void bqzs::Play()
{
	Hero* enemy;
	int attackNum = 0;
	int magicpro = magicPro;
	int pro = protect;
	while (!isDead() && !isWin(&myPlayerData, &opPlayerData)) {
		enemy = getEnemyByDistance(this, opPlayerData);//����
		magicPro = magicpro;
		protect = pro;
		attackNum = 0;
		double add = (level == 1) ? 40 : 65;
		int hurt = (int)(enemy->attackRate * attack);
		while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK) {
			attackNum++;//�Ըõ��˵Ĺ�������+1
			auto lambdb = [=](float dt) {
				bqzs::bqzsnormalAttack(enemy, attackNum,add,hurt);
			};
			this->schedule(lambdb, 1 / speed, "bqzsAttack");
			//�ͷż���
			if (blue == blueMax) {
				int i = 0;
				while (i < 9) {
					attackRate = 0.25;
					auto lambda = [=](float dt) {
						enemy->blood -= (int)(hurt - (enemy->protect) + add);
						bqzs::swordswing("",this);//??????????//picture
					};
					this->schedule(lambda, 1 / speed * 2,"bqzsSkill");//���ٵ��ͷż���
					i++;
				}
				blue = 0;
				attackRate = 1;//�ָ�
			}
			if (enemy->blood < 0)
				enemy->blood = 0;//�з�����
		}
	magicPro = magicpro;
	protect = pro;
	}
}

void bqzs::bqzsnormalAttack(Hero* enemy, double add, int hurt)
{
	blue += 30;
	enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt- enemy->protect;//���׵��������˺�
	swordwaive("sword.png",this);//??????????//picture
}

void bqzs::swordwaive(string picturename, Hero* my)
{
	Sprite* sword = Sprite::create(picturename);
	this->addChild(sword);
	sword->setPosition(Vec2(0, 0)); // ���õ��ĳ�ʼλ��//??????????//���ľ��룿

	// ���赶�Ķ�������
	auto waive = Sequence::create(
		RotateTo::create(0.05f, -45),   // ��������ת
		RotateTo::create(0.1f, 0),      // ���ָ�ԭʼ�Ƕ�
		nullptr
	);
	// ִ�ж�������
	sword->runAction(waive);
}

void bqzs::swordswing(string picturename, Hero* my)
{
	Sprite* sword = Sprite::create(picturename);
	this->addChild(sword);
	sword->setPosition(Vec2(0, 0)); // ���õ��ĳ�ʼλ��//??????????//���ľ��룿

	// ��ת���Ķ�������
	auto swing = Sequence::create(
		RotateTo::create(0.1f, 360),   // ����ת//??????????//����time��
		nullptr
	);
	// ִ�ж�������
	sword->runAction(swing);
}