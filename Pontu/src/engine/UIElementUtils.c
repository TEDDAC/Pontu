#include "engine/UIElementUtils.h"


PositionSpecifier newPositionSpecifier(const SDL_Rect* const base100, const PositionX_Type tpX, const PositionY_Type tpY, const AspectRatioType aspectType) {
	PositionSpecifier ps = {
		.base100 = *base100,
		.tpX = tpX,
		.tpY = tpY,
		.aspectType = aspectType
	};
	return ps;
}

SDL_Rect adaptPosToRect(const PositionSpecifier *const positionSpecifier, const SDL_Rect *const globalRect) {
	SDL_Rect r = {
		.x = 0,
		.y = 0,
		.w = 100,
		.h = 100
	};

	switch (positionSpecifier->aspectType)
	{
	case ASPECT_IGNORE:
		r.w = globalRect->w * positionSpecifier->base100.w/100.0;
		r.h = globalRect->h * positionSpecifier->base100.h/100.0;
		break;
	case ASPECT_KEEP_W:
		r.w = globalRect->w * positionSpecifier->base100.w/100.0;
		r.h =  r.w * positionSpecifier->base100.h/positionSpecifier->base100.w;
		break;
	case ASPECT_KEEP_H:
		r.h = globalRect->h * positionSpecifier->base100.h/100.0;
		r.w =  r.h * positionSpecifier->base100.w/positionSpecifier->base100.h;
		break;
	case ASPECT_KEEP_FIT: {
		const int preferedW = globalRect->w * positionSpecifier->base100.w/100.0;
		const int preferedH = globalRect->h * positionSpecifier->base100.h/100.0;
		const int associatedH = preferedW * positionSpecifier->base100.h/positionSpecifier->base100.w;
		const int associatedW = preferedH * positionSpecifier->base100.w/positionSpecifier->base100.h;

		if (associatedH > preferedH) {
			r.h = preferedH;
			r.w = associatedW;
		}
		else {
			r.w = preferedW;
			r.h = associatedH;
		}
	}
		
		
		break;
	default:
		break;
	}

	switch (positionSpecifier->tpX)
	{
	case POSX_LEFT:
		r.x = globalRect->x + globalRect->w * positionSpecifier->base100.x/100.0;
		break;
	case POSX_CENTER:
		r.x = (globalRect->x + globalRect->w * positionSpecifier->base100.x/100.0) - r.w/2;
		break;
	case POSX_RIGHT:
		r.x = (globalRect->x + globalRect->w * positionSpecifier->base100.x/100.0) - r.w;
		break;
	default:
		break;
	}

	switch (positionSpecifier->tpY)
	{
	case POSY_TOP:
		r.y = globalRect->y + globalRect->h * positionSpecifier->base100.y/100.0;
		break;
	case POSY_CENTER:
		r.y = globalRect->y + globalRect->h * positionSpecifier->base100.y/100.0 - r.h/2;
		break;
	case POSY_BOTTOM:
		r.y = globalRect->y + globalRect->h * positionSpecifier->base100.y/100.0 - r.h;
		break;
	default:
		break;
	}
	
	return r;
}

