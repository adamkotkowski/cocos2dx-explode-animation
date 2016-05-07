#ifndef Explosion_hpp
#define Explosion_hpp

#include <string>
#include <sstream>
#include "cocos2d.h"

using namespace cocos2d;

namespace util{
	class Explosion : public ActionInterval{
		Vec3 crashVector;
		float explosionPower;
		float duration;
		float gravity;
	
	public:
		virtual void startWithTarget(Node *target) override;
		static Explosion* create(float duration, const Vec3& crashVector, float explosionPower, float gravity);
		~Explosion();
	protected:
		void update(float time) override;
		void stop() override;
	private:
		Vector<cocos2d::FiniteTimeAction*> actions;
		Vec3 randomNormalVector();
		bool initWithDuration(float duration, const Vec3& crashVector, float explosionPower, float gravity);
	};
}
#endif /* Explosion_hpp */
