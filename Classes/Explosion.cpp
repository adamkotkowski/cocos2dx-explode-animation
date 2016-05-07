#include "Explosion.hpp"

namespace util {
	void Explosion::startWithTarget(Node *target) {
		for(auto iter = target->getChildren().begin(); iter!=target->getChildren().end(); iter++){
			Vec3 moveVector = randomNormalVector();
			moveVector.normalize();
			Vec3 transformed = target->getWorldToNodeTransform() * crashVector;
			
			auto animationMove = MoveBy::create(duration, moveVector * explosionPower + transformed);
			auto animationFallDown = MoveBy::create(duration, Vec3(1,-gravity,0));
			auto ease = EaseOut::create(animationMove, 3);
			auto animation = Spawn::create(ease, animationFallDown, NULL);
			CallFuncN* callFunc = CallFuncN::create([&](Node* sender){
				sender->removeFromParent();
			});

			auto sequence = Sequence::create(animation, callFunc, NULL);
			sequence->retain();
			actions.pushBack(sequence);
			sequence->startWithTarget(*iter);
		}
	}
	
	bool Explosion::initWithDuration(float duration, const Vec3& crashVector, float explosionPower, float gravity) {
		ActionInterval::initWithDuration(duration);
		this->duration = duration;
		this->crashVector = crashVector;
		this->explosionPower = explosionPower;
		this->gravity = gravity;
		return true;
	}
	
	Explosion* Explosion::create(float duration, const Vec3& crashVector, float explosionPower, float gravity){
		Explosion *ret = new (std::nothrow) Explosion();
		if (ret)
		{
			if (ret->initWithDuration(duration, crashVector, explosionPower, gravity))
			{
				ret->autorelease();
			}
			else
			{
				delete ret;
				ret = nullptr;
			}
		}
		return ret;
	}
	Vec3 Explosion::randomNormalVector(){
		Vec3 ret((rand_0_1()*2)-1, (rand_0_1()*2)-1, (rand_0_1()*2)-1);
		ret.normalize();
		return ret;
	}
	
	Explosion::~Explosion()
	{
		for(auto iter = actions.begin(); iter!= actions.end(); iter++){
			CC_SAFE_RELEASE(*iter);
		}
	}
	
	void Explosion::stop()
	{
		for(auto iter = actions.begin(); iter!= actions.end(); iter++){
			(*iter)->stop();
		}
		ActionInterval::stop();
	}
	
	void Explosion::update(float time)
	{
		for(auto iter = actions.begin(); iter!= actions.end(); iter++){
			(*iter)->update(time);
		}
	}
	
}