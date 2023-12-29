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
	state = 1;//技能状态
	price = 1;//花费
	speed = 0.6;//攻速
}

void bqzs::upLevelbqzs(Hero* bqzs1, Hero* bqzs2, Hero* bqzs3)
{
	bqzs1->blood = 1080;//当前血量
	bqzs1->maxBlood = 1080;//生命值
	bqzs1->level = 2; //等级
	bqzs1->attack = 90; //攻击力
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
	static Hero* enemy = getEnemyByDistance(this, false, this->ofPlayer);//锁敌
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
			attackNum++;//对该敌人的攻击次数+1
			auto lambdb = [=](float dt) {
				bqzs::bqzsnormalAttack(enemy,hurt,add);
			};
			this->schedule(lambdb, 1 / speed, "bqzsAttack");
			auto lambdc = [=](float dt) {
				enemy->setColor(Color3B::RED);
			};
			this->schedule(lambdc, speed, "tmp");
			//释放技能
			if (blue == blueMax) {
				int i = 0;
				while (i < 9) {
					attackRate = 0.25;
					auto lambda = [=](float dt) {
						enemy->blood -= (int)(hurt - (enemy->protect) + add);
						//bqzs::swordswing("",this);//??????????//picture
					};
					this->schedule(lambda, 1 / speed * 2,"bqzsSkill");//快速的释放技能
					//释放技能时候敌人变成橙色
					auto lambdc = [=](float dt) {
						enemy->setColor(Color3B::BLACK);
					};
					this->schedule(lambdc, 1/speed*2, "tmp11");
					i++;
				}
				blue = 0;
				attackRate = 1;//恢复
			}
			if (enemy->blood < 0)
				enemy->blood = 0;//敌方死亡
		//}
	magicPro = magicpro;
	protect = pro;
	//}
	//this->removeFromParent();
}

void bqzs::bqzsnormalAttack(Hero* enemy,int hurt, double add)
{
	blue += 30;
	enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt- enemy->protect;//护甲抵消部分伤害
	enemy->setColor(Color3B::ORANGE);
	//swordwaive("sword.png",this);//??????????//picture
}

//void bqzs::swordwaive(string picturename, Hero* my)
//{
//	Sprite* sword = Sprite::create(picturename);
//	this->addChild(sword);
//	sword->setPosition(Vec2(0, 0)); // 设置刀的初始位置//??????????//更改距离？
//
//	// 挥舞刀的动作序列
//	auto waive = Sequence::create(
//		RotateTo::create(0.05f, -45),   // 刀向左旋转
//		RotateTo::create(0.1f, 0),      // 刀恢复原始角度
//		nullptr
//	);
//	// 执行动作序列
//	sword->runAction(waive);
//}
//
//void bqzs::swordswing(string picturename, Hero* my)
//{
//	Sprite* sword = Sprite::create(picturename);
//	this->addChild(sword);
//	sword->setPosition(Vec2(0, 0)); // 设置刀的初始位置//??????????//更改距离？
//
//	// 旋转刀的动作序列
//	auto swing = Sequence::create(
//		RotateTo::create(0.1f, 360),   // 刀旋转//??????????//更改time？
//		nullptr
//	);
//	// 执行动作序列
//	sword->runAction(swing);
//}