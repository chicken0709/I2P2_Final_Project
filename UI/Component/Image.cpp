#include <allegro5/allegro.h>
#include <memory>

#include "Engine/IObject.hpp"
#include "Image.hpp"

#include "Engine/LOG.hpp"
#include "Engine/Point.hpp"
#include "Engine/Resources.hpp"

namespace Engine {
	Image::Image(std::string img, float x, float y, float w, float h, float anchorX, float anchorY) :
		IObject(x, y, w, h, anchorX, anchorY) {
		if (Size.x == 0 && Size.y == 0) {
			bmp = Resources::GetInstance().GetBitmap(img);
			Size.x = GetBitmapWidth();
			Size.y = GetBitmapHeight();
		}
		else if (Size.x == 0) {
			bmp = Resources::GetInstance().GetBitmap(img);
			Size.x = GetBitmapWidth() * Size.y / GetBitmapHeight();
		}
		else if (Size.y == 0) {
			bmp = Resources::GetInstance().GetBitmap(img);
			Size.y = GetBitmapHeight() * Size.x / GetBitmapWidth();
		}
		else /* Size.x != 0 && Size.y != 0 */ {
			bmp = Resources::GetInstance().GetBitmap(img, Size.x, Size.y);
		}
	}

	Image::Image(int isAnimation,int frameCount,std::string img, float x, float y, float w, float h, float anchorX, float anchorY) :
		IObject(x, y, w, h, anchorX, anchorY) {
		if(isAnimation == 0) {
			if (Size.x == 0 && Size.y == 0) {
				bmp = Resources::GetInstance().GetBitmap(img);
				Size.x = GetBitmapWidth();
				Size.y = GetBitmapHeight();
			}
			else if (Size.x == 0) {
				bmp = Resources::GetInstance().GetBitmap(img);
				Size.x = GetBitmapWidth() * Size.y / GetBitmapHeight();
			}
			else if (Size.y == 0) {
				bmp = Resources::GetInstance().GetBitmap(img);
				Size.y = GetBitmapHeight() * Size.x / GetBitmapWidth();
			}
			else /* Size.x != 0 && Size.y != 0 */ {
				bmp = Resources::GetInstance().GetBitmap(img, Size.x, Size.y);
			}
		}
		else if(isAnimation == 1) {
			if (Size.x == 0 && Size.y == 0) {
				bmp = Resources::GetInstance().GetBitmap(img);
				Size.x = GetBitmapWidth()/frameCount * 1.6;
				Size.y = GetBitmapHeight() * 1.6;
				Engine::LOG(Engine::INFO) << "size x " << Size.x << "size y " << Size.y;
			}
		}
		else if(isAnimation == 2) {
			if (Size.x == 0 && Size.y == 0) {
				bmp = Resources::GetInstance().GetBitmap(img);
				Size.x = GetBitmapWidth()/frameCount*1.6 ;
				Size.y = GetBitmapHeight()*1.6 ;
				Engine::LOG(Engine::INFO) << "size x " << Size.x << "size y " << Size.y;
			}
		}

	}

	void Image::Draw() const {
		al_draw_scaled_bitmap(bmp.get(), 0, 0, GetBitmapWidth(), GetBitmapHeight(),
			Position.x - Anchor.x * GetBitmapWidth(), Position.y - Anchor.y * GetBitmapHeight(),
			Size.x, Size.y, 0);
	}
	int Image::GetBitmapWidth() const {
		return al_get_bitmap_width(bmp.get());
	}
	int Image::GetBitmapHeight() const {
		return al_get_bitmap_height(bmp.get());
	}
}
