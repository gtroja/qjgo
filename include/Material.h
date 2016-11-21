#ifndef MATERIAL_H
#define MATERIAL_H 

class Material{
public:
	void setMaterial(unsigned char R, unsigned char G, unsigned char B, unsigned char A);

	void setR(unsigned char v);
	void setG(unsigned char v);
	void setB(unsigned char v);
	void setA(unsigned char v);

	unsigned char getR();
	unsigned char getG();
	unsigned char getB();
	unsigned char getA();

private:
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
	
};
#endif