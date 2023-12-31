#include "bqzs.h"

bqzs::bqzs()
{
	name = "不屈战神", skillname = "审判", advice = "前排";
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

void bqzs::upLevel(Hero* bqzs1)
{
	bqzs1->blood = 1080;//当前血量
	bqzs1->maxBlood = 1080;//生命值
	bqzs1->level = 2; //等级
	bqzs1->attack = 90; //攻击力
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
	static Hero* enemy = getEnemyByDistance(this, false, this->ofPlayer);//锁敌
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
		enemy = getEnemyByDistance(this, false, this->ofPlayer);//锁敌
		if (enemy != nullptr &&state==ATTACK )
		{
			bqzs::bqzsnormalAttack(enemy, hurt, add);
			attackNum++;//对该敌人的攻击次数+1
		}
	};
	this->schedule(lambdb, 1 / speed, "bqzsAttack");
	//释放技能
	if (blue == blueMax) {
		attackRate = 0.25;
		auto lambda = [=](float dt) {
			enemy->blood -= (int)(hurt - (enemy->protect) + add);
			//bqzs::swordswing(this);
		};
		this->scheduleOnce(lambda, 1 / speed * 2, "bqzsSkill");//快速的释放技能
		blue = 0;
		attackRate = 1;//恢复
	}
	if (enemy->blood < 0)
		enemy->blood = 0;//敌方死亡
	magicPro = magicpro;
	protect = pro;
}

void bqzs::bqzsnormalAttack(Hero* enemy, int hurt, double add)
{
	blue += 30;
	enemy->protect > hurt ? enemy->blood -= 0 : enemy->blood -= hurt - enemy->protect;//护甲抵消部分伤害
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
	// 挥舞刀的动作序列
	auto waive = Sequence::create(
		RotateTo::create(1.0f, 90),   // 刀向左旋转
		RotateTo::create(1.0f, 0),      // 刀恢复原始角度
		CallFunc::create([sword]() {
			sword->removeFromParent();
			}),
		nullptr
				);
	// 执行动作序列
	sword->runAction(waive);
}

//void bqzs::swordswing(Hero* my)
//{
//	Sprite* sword = Sprite::create("./hero/sword.png");
//	my->addChild(sword, 3);
//	sword->setScale(2.0f);
//	sword->setPosition(Vec2(600, 300));
//
//	// 旋转刀的动作序列
//	auto swing = Sequence::create(
//		RotateTo::create(1.0f, 360),
//		CallFunc::create([sword]() {
//			sword->removeFromParent();
//			}),
//		nullptr
//				);
//	// 执行动作序列
//	sword->runAction(swing);
//}