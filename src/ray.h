//Ray header file
class  xyz
{
public:
	float x;
	float y;
	float z;

	xyz(){}
	xyz(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;	
	}
	void pup(PUP::er &p){
	  p | x;
	  p | y;
	  p | z;
	}
	
};

struct vecteur {
	float x, y, z;

    vecteur& operator += (const vecteur &v2){
	    	this->x += v2.x;
        	this->y += v2.y;
        	this->z += v2.z;
	    return *this;
    }
};

inline xyz operator + (const xyz &p, const vecteur &v){
	xyz p2;
	p2.x = p.x + v.x, p2.y = p.y + v.y, p2.z = p.z + v.z;
	return p2;
}

inline xyz operator - (const xyz &p, const vecteur &v){
	xyz p2;
	p2.x = p.x - v.x, p2.y = p.y - v.y, p2.z = p.z - v.z;
	return p2;
}

inline vecteur operator + (const vecteur &v1, const vecteur &v2){
	vecteur v={v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	return v;
}

inline vecteur operator - (const xyz &p1, const xyz &p2){
	vecteur v={p1.x - p2.x, p1.y - p2.y, p1.z - p2.z };
	return v;
}

inline vecteur operator * (float c, const vecteur &v)
{
	vecteur v2={v.x *c, v.y * c, v.z * c };
	return v2;
}

inline vecteur operator - (const vecteur &v1, const vecteur &v2){
	vecteur v={v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	return v;
}

inline float operator * (const vecteur &v1, const vecteur &v2 ) {
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

struct ray {
	xyz start;
	vecteur dir;
};

struct light {
	xyz origin;
	float r, g, b;
};
