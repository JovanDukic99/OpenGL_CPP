class Image {
private:
	int width;
	int height;
	int** buffer;

public:
	// constructors / destructors
	Image(int width, int height);
	Image(const Image& image);
	~Image();

	// operator overload
	int* operator[](int index);

	// getters
	int getWidth();
	int getHeight();

private:
	// init
	void init();
	
	// setters
	void setWidth(int width);
	void setHeight(int height);
	void fillBuffer(const Image& image);
};