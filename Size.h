#pragma once

namespace myNamespace {
	class Size
	{
	public:
		Size();
		Size(unsigned int w, unsigned int h);
		Size& operator=(const Size& other);

		unsigned int sizeWidth() { return m_width; }
		unsigned int sizeHeight() { return m_height; }
	private:
		unsigned int m_width;
		unsigned int m_height;
	};
}


