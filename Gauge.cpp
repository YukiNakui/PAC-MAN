#include "Gauge.h"
#include"Engine/Image.h"

Gauge::Gauge(GameObject* parent)
	:GameObject(parent,"Gauge"),hGaugeBar_(-1),hGaugeFrame_(-1),
	gaugeMaxVal_(200),gaugeCrrVal_(100)
{
}

void Gauge::Initialize()
{
	hGaugeBar_ = Image::Load("GaugeBar.png");
	assert(hGaugeBar_ >= 0);
	hGaugeFrame_ = Image::Load("GaugeFrame.png");
	assert(hGaugeFrame_ >= 0);
	transform_.position_.x = 0.0f;
	transform_.position_.y = 0.85f;
}

void Gauge::Update()
{
}

void Gauge::Draw()
{
	Transform tr = this->transform_;
	tr.position_.x = -0.398f;
	tr.scale_.x = (float)gaugeCrrVal_ / (float)gaugeMaxVal_;
	Image::SetTransform(hGaugeBar_, tr);
	Image::Draw(hGaugeBar_);
	Image::SetTransform(hGaugeFrame_, transform_);
	Image::Draw(hGaugeFrame_);
}

void Gauge::Release()
{
}
