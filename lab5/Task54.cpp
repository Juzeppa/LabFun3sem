#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#define MAX_KARA 2
#define BASE 10


class LongMath
{
friend void make_zeros(LongMath &a, const size_t size, const size_t zeros);
friend void biba(LongMath &a, LongMath &b);


private:
	size_t size;
	int *data;
	int sign;	

	void vector_append();
	void long_short_sum(const int b);
	void long_short_mult(const int a);
    void long_long_sum(const LongMath &other);
    void long_long_sub(const LongMath &other);
    void del_zeros();
    LongMath naive_mult(LongMath a, LongMath b);
    LongMath karatsuba(LongMath a, LongMath b);
    void drop_from_array(int *array, size_t size);
    

public:
    LongMath new_karatsuba(LongMath a, LongMath b);
	LongMath();
	LongMath(const char *num);
    LongMath(const int num);
	LongMath(const LongMath &other);
    ~LongMath();
    LongMath& operator =(const LongMath &other);
    LongMath& operator +=(const LongMath &other);
    LongMath& operator++();
    LongMath& operator -=(const LongMath &other);
    LongMath operator -() const;
    LongMath& operator *=(const LongMath &other);
    LongMath& operator /=(const LongMath &other);
    LongMath& operator %=(const LongMath &other);
    
    bool operator ==(const LongMath &other);
    bool operator !=(int other);
    bool operator <(const LongMath &other);
    bool operator >(const LongMath &other);
    bool operator <=(const LongMath &other);
    bool operator >=(const LongMath &other);
    

    LongMath long_pow(int power);
    LongMath ABS() const;
    size_t getSize() const;
    int* getData() const;
    int getSign() const;
    void print_data() const; 
};

LongMath operator +(const LongMath& left, const LongMath& right);
LongMath operator -(const LongMath& left, const LongMath& right);
LongMath operator *(const LongMath& left, const LongMath& right);
LongMath operator /(const LongMath& left, const LongMath& right);
LongMath operator %(const LongMath& left, const LongMath& right);
char* LMtoStr(LongMath &num, int b);
void reverse(char *str);
std::ostream& operator << (std::ostream& stream, const LongMath& toOutput);


//↓↓↓↓↓↓↓Конструкторы и деструктор↓↓↓↓↓↓↓ 

LongMath::LongMath()
{
	size = 1;
	sign = 1;
	data = new int[1];
	data[0] = 0;
};

LongMath::LongMath(const int num)
{
    int buf = abs(num);
    size_t i = 0;
    size = 0;
    while (buf)
    {
        buf /= BASE;
        size++;
    }
    sign = num > 0 ? 1 : -1;
    data = new int[size];
    buf = abs(num);
    while (buf)
    {     
        data[i++] = buf % BASE;
        buf /= BASE; 
    }
}
LongMath::LongMath(const char *num)
{
	size = 0;
	data = NULL;
	if (*num == '-')
	{
		num++;
		sign = -1;
	}
	else
		sign = 1;
    num--;
	while (*++num)
	{
		long_short_mult(10);
		long_short_sum(*num - '0');
	}

};



LongMath::LongMath(const LongMath &other)
{
    size = other.size;
    sign = other.sign;

    data = new int[size];
    for (size_t i = 0; i < size; i++)
        data[i] = other.data[i]; 
};


LongMath::~LongMath()
{
	size = 0;
	delete [] data;
};

//↓↓↓↓↓↓↓Перегрузка операторов↓↓↓↓↓↓↓
//↓↓↓↓↓↓↓Перегрузка ариметических операций↓↓↓↓↓↓↓
LongMath& LongMath::operator =(const LongMath &other)
{
    size = other.size;
    sign = other.sign;

    if (data) delete[] data;
    
    data = new int[size];
    for (size_t i = 0; i < size; i++)
    {
        data[i] = other.data[i]; 
    }
    
};


LongMath& LongMath::operator +=(const LongMath &other)
{
	long_long_sum(other);
	return *this;
};


LongMath operator +(const LongMath& left, const LongMath& right)
{
    LongMath temp = left;
	temp += right;
	return temp;
}


LongMath& LongMath::operator++()
{
    LongMath one("1");
    *this += one;
    return *this;
}


LongMath& LongMath::operator -=(const LongMath &other)
{
	long_long_sub(other);
	return *this;
};


LongMath LongMath::operator-() const
{
    LongMath temp = *this;
    temp.sign = sign == 1? -1:1;
    return temp;
}


LongMath operator -(const LongMath& left, const LongMath& right)
{
    LongMath temp = left;
	temp -= right;
	return temp;
}


LongMath& LongMath::operator *=(const LongMath &other)
{
	LongMath temp;
	int temp_sign;

	temp_sign = sign * other.sign;
	*this = karatsuba(*this, other);
	sign = temp_sign;
	return *this;
}


LongMath operator *(const LongMath& left, const LongMath& right)
{
    LongMath temp = left;
	temp *= right;
	return temp;
}


LongMath& LongMath::operator /=(const LongMath &other)
{   
    LongMath temp = (*this).ABS();
    LongMath counter("0");
    while (temp > other.ABS())
    {
        temp -= other.ABS();
        ++counter;
    }
    
    counter.sign = sign * other.sign;
    *this = counter;
    del_zeros();
    return *this;
}


LongMath operator /(const LongMath& left, const LongMath& right)
{
    LongMath temp = left;
	temp /= right;
	return temp;
}


LongMath& LongMath::operator %=(const LongMath &other)
{
    LongMath temp = (*this).ABS();
    while (temp > other.ABS())
    {
        temp -= other.ABS();
    }
    temp.sign = sign;
    *this = temp;
    return *this;  
};


LongMath operator %(const LongMath& left, const LongMath& right)
{
    LongMath temp = left;
	temp %= right;
	return temp;
}


//↓↓↓↓↓↓↓Перегрузка логических операций↓↓↓↓↓↓↓
bool LongMath::operator ==(const LongMath &other)
{
	if (size != other.size || sign != other.sign)
		return (false);
	for (int i = 0; i < size; i++)
		if (data[i] != other.data[i])
			return (false);
	return (true);
}

bool LongMath::operator !=(int other)
{
	return (data[0] != other || size > 1);
}

bool LongMath::operator <(const LongMath &other)
{
	if (sign < other.sign)
		return (true);
	else if (sign > other.sign)
		return (false);

	for (int i = size - 1; i >= 0; i--)
	{
		if (data[i] < other.data[i])
			if (sign == -1)
                return (false);
            else return (true);
		else if (data[i] > other.data[i])
            if (sign == -1)
                return (true);
        	else return (false);
        
	}
	return (false);
};


bool LongMath::operator >(const LongMath &other)
{
    return !(*this < other || *this == other);
};


bool LongMath::operator <=(const LongMath &other)
{
    return (*this < other || *this == other);
};


bool LongMath::operator >=(const LongMath &other)
{
    return !(*this < other);
};
//↓↓↓↓↓↓↓Вспомогательные функции↓↓↓↓↓↓↓ 

void LongMath::drop_from_array(int *array, size_t arr_size)
{
    size = arr_size;
	data = (int*)malloc(sizeof(int) * size);
	for (size_t i = 0; i < size; i++)
		data[i] = array[i];
}


void make_zeros(LongMath &a, const size_t size, const size_t zeros)
{
	if (size == zeros)
	{
		delete[] a.data;
		a.data = (int*)calloc(size, sizeof(int));	
	}
	else 
	{
		int *new_data = new int[size];
		for (int j = zeros - 1, i = size - 1; i >= zeros; i--, j--)
		{
			new_data[i] = a.data[j];
			a.data[j] = 0;
		}
		delete [] a.data; 
		a.data = new_data;
	}
	a.size = size; 
	return;
}

LongMath LongMath::naive_mult(LongMath a, LongMath b)
{

	size_t len = a.size;
    LongMath res;
	res.data = (int*)calloc(2 * len, sizeof(int) );
	res.size = 2 * len;
	for (size_t i = 0; i < len; ++i) {
        for (size_t j = 0; j < len; ++j) {
            res.data[i + j] += a.data[i] * b.data[j];
        }
    }

    for (size_t i = 0; i < len * 2 - 1; ++i)
	{
	    if (res.data[i] >= BASE)
	    { //если число больше максимального, то организовавается перенос
	      int carryover = res.data[i] / BASE;
	      res.data[i + 1] += carryover;
	      res.data[i] -= carryover * BASE;
	    }
	    else if (res.data[i] < 0)
	    { //если меньше - заем
	      int carryover = (res.data[i] + 1) / BASE - 1;
	      res.data[i + 1] += carryover;
	      res.data[i] -= carryover * BASE;
	    }
  	}
    

    //std::cout << res << std::endl;     
    return res;
}	


LongMath LongMath::new_karatsuba(LongMath a, LongMath b)
{
	size_t len = a.size;
	LongMath res;
	res.data = (int*)calloc(2 * len, sizeof(int) );
	res.size = 2 * len;
	if (len <= MAX_KARA)
	{
		return naive_mult(a, b);
	}

	size_t k = len / 2;

	LongMath ar, al, br, bl;
	ar.data = new int[k]; 
	al.data = new int[k]; 
	br.data = new int[k]; 
	bl.data = new int[k];
	ar.size = br.size = k; 
	al.size = bl.size = k;

	for (size_t i = 0; i < k; i++)
	{
		ar.data[i] = a.data[i];
		al.data[i] = a.data[i + k];
		br.data[i] = b.data[i];
		bl.data[i] = b.data[i + k];
	}

	LongMath P1 = new_karatsuba(al, bl);
	LongMath P2 = new_karatsuba(ar, br);
	

	LongMath alr, blr;
	alr.size = blr.size = k + 1;
	alr.data = new int[k + 1];
	blr.data = new int[k + 1];

	for (size_t i = 0; i < k; i++)
	{
		alr.data[i] = al.data[i] + ar.data[i];		
		blr.data[i] = bl.data[i] + br.data[i];	
	}

	for (size_t i = 0; i < k; ++i)
	{
	    if (alr.data[i] >= BASE)
	    { //если число больше максимального, то организовавается перенос
	      int carryover = alr.data[i] / BASE;
	      alr.data[i + 1] += carryover;
	      alr.data[i] -= carryover * BASE;
	    }
	    else if (alr.data[i] < 0)
	    { //если меньше - заем
	      int carryover = (alr.data[i] + 1) / BASE - 1;
	      alr.data[i + 1] += carryover;
	      alr.data[i] -= carryover * BASE;
	    }
  	}

	for (size_t i = 0; i < k; ++i)
	{
	    if (blr.data[i] >= BASE)
	    { //если число больше максимального, то организовавается перенос
	      int carryover = blr.data[i] / BASE;
	      blr.data[i + 1] += carryover;
	      blr.data[i] -= carryover * BASE;
	    }
	    else if (blr.data[i] < 0)
	    { //если меньше - заем
	      int carryover = (blr.data[i] + 1) / BASE - 1;
	      blr.data[i + 1] += carryover;
	      blr.data[i] -= carryover * BASE;
	    }
  	}

	LongMath P3 = new_karatsuba(alr, blr);
	

	for (int i = 0; i < len; ++i)
	{
		P3.data[i] -= P2.data[i] + P1.data[i]; 
	}


	for (int i = 0; i < len; ++i)
	{
		res.data[i] = P2.data[i]; 
	}

	for (int i = len; i < len * 2; ++i)
	{
		res.data[i] = P1.data[i - len]; 
	}

	for (int i = k; i < len + k; ++i)
	{
		res.data[i] += P3.data[i - k]; 
	}

	for (size_t i = 0; i < len * 2 - 1; ++i)
	{
	    if (res.data[i] >= BASE)
	    { //если число больше максимального, то организовавается перенос
	      int carryover = res.data[i] / BASE;
	      res.data[i + 1] += carryover;
	      res.data[i] -= carryover * BASE;
	    }
	    else if (res.data[i] < 0)
	    { //если меньше - заем
	      int carryover = (res.data[i] + 1) / BASE - 1;
	      res.data[i + 1] += carryover;
	      res.data[i] -= carryover * BASE;
	    }
  	}
	
	// std::cout << al << " " << ar  << std::endl;
	// std::cout << bl << " " << br << std::endl;
	return res;
}


LongMath LongMath::karatsuba(LongMath a, LongMath b) 
{
	LongMath product;
	int i;

	product.size = a.size + b.size;
	product.data = (int*)malloc(sizeof(int) * product.size);

	if (a.size < MAX_KARA)
	{
		long long cur;
		long long carry;

		memset(product.data, 0, sizeof(int) * product.size);
		for (int i = 0; i < a.size; ++i)
			for (int j = 0, carry = 0; j < b.size || carry; ++j)
			{
				cur = product.data[i+j] + a.data[i] * 1ll * (j < (int)b.size ? b.data[j] : 0) + carry;
				product.data[i+j] = int (cur % BASE);
				carry = int (cur / BASE);
			}
		product.del_zeros();
		return (product);
	}

	LongMath a_part1; 
	a_part1.drop_from_array(a.data, (a.size + 1) / 2);


	LongMath a_part2;
	a_part2.drop_from_array(a.data + a_part1.size, a.size / 2);

	LongMath b_part1;
	b_part1.drop_from_array(b.data, (b.size + 1) / 2);

	LongMath b_part2;
	b_part2.drop_from_array(b.data + b_part1.size, b.size / 2);

	LongMath sum_of_a_parts = a_part1 + a_part2;
    sum_of_a_parts.del_zeros();

	LongMath sum_of_b_parts = b_part1 + b_part2;
    sum_of_b_parts.del_zeros();

	LongMath product_of_sums_of_parts = karatsuba(sum_of_a_parts, sum_of_b_parts);
	LongMath product_of_first_parts = karatsuba(a_part1, b_part1);
	LongMath product_of_second_parts = karatsuba(a_part2, b_part2);
	LongMath sum_of_middle_terms = product_of_sums_of_parts - product_of_first_parts - product_of_second_parts;
    std::cout<< product_of_first_parts<< std::endl;
    std::cout<< product_of_second_parts<< std::endl;
    std::cout<< sum_of_middle_terms<< std::endl;
	memcpy(product.data, product_of_first_parts.data,
			product_of_first_parts.size * sizeof(int));
	memcpy(product.data + product_of_first_parts.size,
			product_of_second_parts.data, product_of_second_parts.size * sizeof(int));
    product.del_zeros();
    std::cout<< product<< std::endl;
	int carry = 0;
	carry = 0;
	for (i = 0; i < sum_of_middle_terms.size || carry; ++i)
	{
		if (i == product.size)
			product.vector_append();
		product.data[a_part1.size + i] += sum_of_middle_terms.data[i] + carry;
		carry = product.data[a_part1.size + i] >= BASE;
		if (carry)
			product.data[a_part1.size + i] -= BASE;
	}
    std::cout<< product<< std::endl;
	return (product);
}




void LongMath::vector_append()
{
	size++;
	if (size == 1)
	{
		data = new int[1];
		data[0] = 0;
		return;
	}
	data = (int*)realloc(data, sizeof(int) * size);
	data[size - 1] = 0;
};

void LongMath::long_long_sum(const LongMath &other)
{
	int i = -1;
	int temp = 0;


	if (!size)
		vector_append();
    if (sign == other.sign)
    {
        while (++i < std::max(size, other.size) || temp)
		{
			if (i == size)
				vector_append();
			data[i] += (other.size > i ? other.data[i] : 0) + temp;
			temp = data[i] >= BASE;
			if (temp)
				data[i] -= BASE;
                
		}
    }
    else if (sign == -1)
        {
            sign = 1;
            long_long_sub(other);
            sign = -sign;    
        }
    else if (sign == 1)
        {
            sign = -1;
            long_long_sub(other);
            sign = -sign;
        }
    del_zeros();
};


void LongMath::long_long_sub(const LongMath &other)
{
	int temp = 0;
	
	if (sign == other.sign && other.sign == 1)
	{
		if (*this >= other)
		{
			for (size_t i = 0; i < size || temp; ++i)
			{
				data[i] -= temp + (i < other.size ? other.data[i] : 0);
				temp = data[i] < 0;
				if (temp) data[i] += BASE;
			}
		}
		else
		{
			
			for (size_t i = 0; i < other.size || temp; ++i)
			{
				other.data[i] -= temp + (i < size ? data[i] : 0);
				temp = other.data[i] < 0;
				if (temp) other.data[i] += BASE;
                *this = other; 
                sign = -1;
			}
		}
	}
	else if (sign == other.sign && other.sign == -1)
    {        
        if (*this <= other)
		{
			for (size_t i = 0; i < size || temp; ++i)
			{
				data[i] -= temp + (i < other.size ? other.data[i] : 0);
				temp = data[i] < 0;
				if (temp) data[i] += BASE;
			}
		}
		else
		{
			sign = 1;
			for (size_t i = 0; i < other.size || temp; ++i)
			{
				other.data[i] -= temp + (i < size ? data[i] : 0);
				temp = other.data[i] < 0;
				if (temp) other.data[i] += BASE;
                *this = other; 
                sign = 1;
			}
		}
    }    
	else
		if (sign == -1)
        {
            sign = 1;
            long_long_sum(other);
            sign = -1;
        }
		else
        {
            sign = -1;
            long_long_sum(other);
            sign = 1;
        }
	
	del_zeros();
}

void LongMath::long_short_mult(const int b)
{
	int	temp = 0;
	int	i = 0;
	long long current = 0;

	if (!size)
		vector_append();
	while (i < size || temp)
	{
		if (i == size)
			vector_append();
		current = temp + data[i] * b;
		data[i] = (current % BASE);
		temp = (current / BASE);
		i++;
	}
};

void LongMath::long_short_sum(const int a)
{
	int i = 1;
	int temp = 0;

	if (!size)
		vector_append();
	data[0] += a;
	temp = data[0] >= BASE;
	if (temp)
		data[0] -= BASE;
	while (temp)
	{
		if (i == size)
			vector_append();
		data[i] += temp;
		temp = data[i] >= BASE;
		if (temp)
			data[i] -= BASE;
		i++;
	}
};


void LongMath::del_zeros()
{
    if (size == 1 && !data[0])
    {
        sign = 1;
        return;
    }
	while (size > 1 && !data[size - 1])
		size--;
	data = (int*)realloc(data, sizeof(int) * size);
};

LongMath LongMath::ABS() const
{
    LongMath temp = *this;
    temp.sign = 1;
    return temp;
}

LongMath LongMath::long_pow(int power)
{
	LongMath res("1");
	LongMath temp = *this;

	while (power)
	{
		if (power & 1) {
			res *= temp;
			power--;
		}
		else {
			temp *= temp;
			power >>= 1;
		}
	}
	return res;
};



size_t LongMath::getSize() const 
{
    return size;
}

int* LongMath::getData() const 
{
    return data;
}

int LongMath::getSign() const
{
    return sign;
}


std::ostream& operator << (std::ostream& stream, const LongMath& toOutput)
{
    toOutput.getSign() < 0? std::cout << '-' : std::cout;
    for (int i = toOutput.getSize() - 1; i >= 0; i--)
    {
        std::cout << toOutput.getData()[i] << " ";
    }
    return stream;
};

int main(int argc, char const *argv[])
{
	
	std::cout<< "hui" << std::endl;
	LongMath a("1234") , b("9876"), c;
	c = a.new_karatsuba(a, b);

	std::cout << c << std::endl;
	return 0;
}