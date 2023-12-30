#include "bqzs.h"

bqzs::bqzs()
{
	name = "不屈战神", skillname = "审判";
	skillType = PHYSICS;//坦克
	blood = 600;
	maxBlood = 600;//血量
	level = 1; //等级
	attack = 50; //攻击力
	protect = 40;//护甲
	magicPro = 20;//魔抗
	magic = 100;
	state = 1;//技能状态
	price = 1;//花费
	x = 0, y = 0;//在棋盘上的坐标
	speed = 0.6;//攻速
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
		enemy = getEnemyByDistance(this, opPlayerData);//锁敌
		magicPro = magicpro;
		protect = pro;
		attackNum = 0;
		double add = (level == 1) ? 40 : 65;
		int hurt = (int)(enemy->attackRate * attack);
		while (!enemy->isDead() && isInAttackRange(this, enemy) && !isDead() && state == ATTACK) {
			attackNum++;//对该敌人的攻击次数+1
			auto lambdb = [=](float dt) {
				bqzs::bqzsnormalAttack(enemy, attackNum,add,hurt);
			};
			this->schedule(lambdb, 1 / speed, "bqzsAttack");
			//释放技能
			if (blue == blueMax) {
				int i = 0;
				while (i < 9) {
					attackRate = 0.25;
					auto lambda = [=](float dt) {
						enemy->blood -= (int)(hurt - (enemy->protect) + add);
						bqzs::swordswing("",this);//??????????//picture
					};
					this->schedule(lambda, 1 / speed * 2,"bqzsSkill");//快速的释放技能
					i++;
				}
				blue = 0;
				attackRate = 1;//恢复
			}
			if (enemy->blood < 0)
				enemy->blood = 0;//敌方死亡
		}
	magicPro = magicpro;
	protect = pro;
	}
}

void bqzs::bqzsnormalAttack(Hero* enemy, double add, int hurt)
{
	blue += 30;
	enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt- enemy->protect;//护甲抵消部分伤害
	swordwaive("sword.png",this);//??????????//picture
}

void bqzs::swordwaive(string picturename, Hero* my)
{
	Sprite* sword = Sprite::create(picturename);
	this->addChild(sword);
	sword->setPosition(Vec2(0, 0)); // 设置刀的初始位置//??????????//更改距离？

	// 挥舞刀的动作序列
	auto waive = Sequence::create(
		RotateTo::create(0.05f, -45),   // 刀向左旋转
		RotateTo::create(0.1f, 0),      // 刀恢复原始角度
		nullptr
	);
	// 执行动作序列
	sword->runAction(waive);
}

void bqzs::swordswing(string picturename, Hero* my)
{
	Sprite* sword = Sprite::create(picturename);
	this->addChild(sword);
	sword->setPosition(Vec2(0, 0)); // 设置刀的初始位置//??????????//更改距离？

	// 旋转刀的动作序列
	auto swing = Sequence::create(
		RotateTo::create(0.1f, 360),   // 刀旋转//??????????//更改time？
		nullptr
	);
	// 执行动作序列
	sword->runAction(swing);
}