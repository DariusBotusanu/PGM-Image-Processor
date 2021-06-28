#include "Size.h"

namespace myNamespace {
	Size::Size() {
		/**
		* Input:
		* Output:
		* Constructor of the class size, initializes the members with 0
		*/
		m_width = 0;
		m_height = 0;
	}

	Size::Size(unsigned int w, unsigned int h) {
		/**
		* Input: w - width, h - height
		* Output:
		* Constructor of the class size, initializes the members m_width and m_height with w and h respectively
		*/
		m_width = w;
		m_height = h;
	}

	Size& Size::operator=(const Size& other) {
		/**
		* Input: constant reference to a Size object
		* Output: reference to a Size object
		* Assignment operator = of the class Size
		*/
		m_width = other.m_width;
		m_height = other.m_height;
		return *this;
	}
}
