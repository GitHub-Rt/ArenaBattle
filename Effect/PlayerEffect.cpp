#include "PlayerEffect.h"

#include "../Engine/VFX.h"
#include "../Engine/Global.h"

#include "../Character/Player.h"


PlayerEffect::PlayerEffect()
{
	eLimitFire = -1;
	eLimitSparks = -1;
	eLimitGround = -1;

	eLimitTornado = -1;
	
	ventilationDir = { 0,0,0 };
	ventilationRotate = { 0,0,0 };
	eLimitVentilation = -1;
};

void PlayerEffect::Release()
{
	VFX::Release();
}

void PlayerEffect::StartEffectDetonation()
{
	//炎
	data_Detonation.textureFileName = "Effect/Player/cloudA.png";
	data_Detonation.delay = 0;
	data_Detonation.number = 80;
	data_Detonation.lifeTime = 30;
	data_Detonation.direction = XMFLOAT3(0, 1, 0);
	data_Detonation.directionRnd = XMFLOAT3(90, 90, 90);
	data_Detonation.speed = 0.1f;
	data_Detonation.speedRnd = 0.8f;
	data_Detonation.size = XMFLOAT2(1.2, 1.2);
	data_Detonation.sizeRnd = XMFLOAT2(0.4, 0.4);
	data_Detonation.scale = XMFLOAT2(1.05, 1.05);
	data_Detonation.color = XMFLOAT4(1, 1, 0.1, 1);
	data_Detonation.deltaColor = XMFLOAT4(0, -1.0 / 20, 0, -1.0 / 20);
	eLimitFire = VFX::Start(data_Detonation);


	//火の粉
	data_Detonation.delay = 0;
	data_Detonation.number = 80;
	data_Detonation.lifeTime = 100;
	data_Detonation.positionRnd = XMFLOAT3(0.5, 0, 0.5);
	data_Detonation.direction = XMFLOAT3(0, 1, 0);
	data_Detonation.directionRnd = XMFLOAT3(90, 90, 90);
	data_Detonation.speed = 0.25f;
	data_Detonation.speedRnd = 1;
	data_Detonation.accel = 0.93f;
	data_Detonation.size = XMFLOAT2(0.1, 0.1);
	data_Detonation.sizeRnd = XMFLOAT2(0.4, 0.4);
	data_Detonation.scale = XMFLOAT2(0.99, 0.99);
	data_Detonation.color = XMFLOAT4(1, 1, 0.1, 1);
	data_Detonation.deltaColor = XMFLOAT4(0, 0, 0, 0);
	data_Detonation.gravity = 0.003f;
	eLimitSparks = VFX::Start(data_Detonation);


	//地面
	data_Detonation.textureFileName = "Effect/Player/flashA_R.png";
	data_Detonation.positionRnd = XMFLOAT3(0, 0, 0);
	data_Detonation.isBillBoard = false;
	data_Detonation.rotate.x = 90;
	data_Detonation.delay = 0;
	data_Detonation.number = 1;
	data_Detonation.lifeTime = 7;
	data_Detonation.speed = 0;
	data_Detonation.size = XMFLOAT2(5, 5);
	data_Detonation.sizeRnd = XMFLOAT2(0, 0);
	data_Detonation.scale = XMFLOAT2(1.25f, 1.25f);
	data_Detonation.color = XMFLOAT4(1, 1, 1, 0.3f);
	eLimitGround = VFX::Start(data_Detonation);

}

void PlayerEffect::StopEffectDetonation()
{
	VFX::End(eLimitFire);
	VFX::End(eLimitSparks);
	VFX::End(eLimitGround);

	Release();
}


void PlayerEffect::StartEffectAtHardAttack()
{
	data_Tornado.textureFileName = "Effect/Player/RingCloud.png";
	data_Tornado.rotate.x = 90;
	data_Tornado.delay = 20;
	data_Tornado.speed = 0.3f;
	data_Tornado.accel = 0.98f;
	data_Tornado.size = XMFLOAT2(2, 2);
	data_Tornado.sizeRnd = XMFLOAT2(0.4, 0.4);
	data_Tornado.scale = XMFLOAT2(1.03, 1.03);
	data_Tornado.color = XMFLOAT4(1, 1, 1, 0.2f);
	data_Tornado.deltaColor = XMFLOAT4(0, 0, 0, -0.003);
	data_Tornado.lifeTime = 45;
	data_Tornado.spin.z = -4;
	data_Tornado.rotateRnd.z = 180;
	data_Tornado.isBillBoard = false;
	eLimitTornado = VFX::Start(data_Tornado);
}

void PlayerEffect::StopEffectAtHardAttack()
{
	VFX::End(eLimitTornado);

	Release();
}

void PlayerEffect::StartEffectAtNormalAttack()
{
	XMFLOAT3 vr = ventilationRotate;
	vr.z += 45;
	data_Ventilation.textureFileName = "Effect/Player/flashA_R.png";
	{
		XMVECTOR vView = {0,0,1,0};
		XMVECTOR vDir = XMLoadFloat3(&ventilationDir);
		XMVECTOR vDot = XMVector3Dot(vView, vDir);
		float dot = XMVectorGetX(vDot);

		float angle = acos(dot);
		XMVECTOR cross = XMVector3Cross(vView, vDir);
		if (XMVectorGetY(cross) < 0)
		{
			angle *= -1;
		}
		float y = angle * 180.0f / 3.14f;
		XMFLOAT3 dir = ventilationDir;
		dir.y = y;
	}
	data_Ventilation.direction = ventilationDir;
	data_Ventilation.directionRnd = XMFLOAT3(0, 0, 0);
	data_Ventilation.rotate = vr;
	data_Ventilation.speed = 1.5f;
	data_Ventilation.position.y += 0.5f;
	data_Ventilation.speedRnd = 0.0f;
	data_Ventilation.delay = 0;
	data_Ventilation.number = 1;
	data_Ventilation.lifeTime = 30;
	//data_Ventilation.spin.z = 5.0f;
	data_Ventilation.size = XMFLOAT2(6, 6);
	//data_Ventilation.sizeRnd = XMFLOAT2(0.4f, 0.4f);
	data_Ventilation.scale = XMFLOAT2(1.04f, 1.04f);
	data_Tornado.color = XMFLOAT4(0.5f, 0.5f, 0.5f, 0.5f);
	data_Ventilation.isBillBoard = false;
	eLimitVentilation = VFX::Start(data_Ventilation);
	{
		
		vr.z += 90;
		data_Ventilation.rotate = vr;
	}
	eLimitVentilation = VFX::Start(data_Ventilation);
}

void PlayerEffect::StopEffectAtNormalAttack()
{
	VFX::End(eLimitVentilation);

	Release();
}

void PlayerEffect::SetEmitterPosition(XMFLOAT3 pos, EmitterType type)
{
	switch (type)
	{
	case EmitterType::Detonation:	//爆破エフェクト
		data_Detonation.position = pos;
		break;
	case EmitterType::Ventilation:	//風切りエフェクト
		data_Ventilation.position = pos;
		break;
	case EmitterType::Tornado:	//竜巻エフェクト
		data_Tornado.position = pos;
		break;
	default:
		break;
	}
}