#include<Maths.h>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec3                       /////////////////////////////////////////////////////

float Vec3::GetMagnitude() const
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//Working kinda.. Magnitude of the vector isnt always 1 but rather between 1.0 and 1.4 not sure about it
void Vec3::Normalize()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
    z /= GetMagnitude();
}

float edgeFunction(const Vec3& a, const Vec3& b, const Vec3& c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

float edgeFunction(const Vec4& a, const Vec4& b, const Vec4& c)
{
    return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
}

Vec3 Vec3::GetBarycentricCoords(const Vec3& p0, const Vec3& p1, const Vec3& p2)
{
    Vec3 barycentricCoords;

    float area = edgeFunction(p0, p1, p2);
    float w0 = edgeFunction(p1, p2, *this);
    float w1 = edgeFunction(p2, p0, *this);
    float w2 = edgeFunction(p0, p1, *this);

    if (w0 <= 0 and w1 <= 0 and w2 <= 0)
    {
        barycentricCoords.x = w0 / area;
        barycentricCoords.y = w1 / area;
        barycentricCoords.z = w2 / area;
    }
    return barycentricCoords;
}

bool Vec3::operator==(const Vec3& a)
{
    if (this->x == a.x && this->y == a.y && this->z == a.z)
        return true;

    return false;
}

Vec3 operator+(const Vec3& a, const Vec3& b)
{
    Vec3 c(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z
    );
    return c;
}

Vec3 operator*(const Vec3& a, const float b)
{
    Vec3 c(
        a.x * b,
        a.y * b,
        a.z * b
    );
    return c;
}

Vec3 operator*(const float b, const Vec3& a)
{
    Vec3 c(
        a.x * b,
        a.y * b,
        a.z * b
    );
    return c;
}

Vec3 operator*(const Vec3& a, const Vec3& b)
{
    Vec3 d(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
    return d;
}

Vec3 operator-(const Vec3& a, const Vec3& b)
{
    Vec3 d(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z
    );
    return d;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Vec4                       /////////////////////////////////////////////////////

void Vec4::Homogenize()
{
    if (w != 0)
    {
        x /= w;
        y /= w;
        z /= w;
    }
}

Vec4 Vec4::GetHomogenizedVec()
{
    Vec4 vec = Vec4();
    if (w != 0)
    {
        vec.x = this->x / w;
        vec.y = this->y / w;
        vec.z = this->z / w;
    }

    return vec;
}

float Vec4::GetMagnitude()
{
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

//Working kinda.. Magnitude of the vector isnt always 1 but rather between 1.0 and 1.4 not sure about it
void Vec4::Normalize()
{
    x /= GetMagnitude();
    y /= GetMagnitude();
    z /= GetMagnitude();
    //  w /= GetMagnitude();
}

bool Vec4::IsInTriangle(const Vec4& p0, const Vec4& p1, const Vec4& p2)
{
    float e01 = (this->x - p0.x) * (p1.y - p0.y) - (this->y - p0.y) * (p1.x - p0.x);
    float e12 = (this->x - p1.x) * (p2.y - p1.y) - (this->y - p1.y) * (p2.x - p1.x);
    float e20 = (this->x - p2.x) * (p0.y - p2.y) - (this->y - p2.y) * (p0.x - p2.x);

    if (e01 <= 0 && e12 <= 0 && e20 <= 0)
        return true;
    else
        return false;
}

void Vec4::GetNewZForZBuffer()
{
    this->z = 2 * (this->z - 10) / (100 - 10) - 1;
}

Vec4 Vec4::GetBarycentricCoords(const Vec4& p0, const Vec4& p1, const Vec4& p2)
{
    Vec4 barycentricCoords;

    float area = edgeFunction(p0, p1, p2);
    float w0 = edgeFunction(p1, p2, *this);
    float w1 = edgeFunction(p2, p0, *this);
    float w2 = edgeFunction(p0, p1, *this);

    if (w0 <= 0 and w1 <= 0 and w2 <= 0)
    {
        barycentricCoords.x = w0 / area;
        barycentricCoords.y = w1 / area;
        barycentricCoords.z = w2 / area;
    }
    return barycentricCoords;
}

Vec4 operator+(const Vec4& a, const Vec4& b)
{
    Vec4 c(
        a.x + b.x,
        a.y + b.y,
        a.z + b.z,
        a.w + b.w
    );
    return c;
}

Vec4 operator-(const Vec4& a, const Vec4& b)
{
    Vec4 c(
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        a.w - b.w
    );
    return c;
}

Vec4 operator*(const Vec4& a, const float b)
{
    Vec4 c(
        a.x * b,
        a.y * b,
        a.z * b,
        a.w * b
    );
    return c;
}

void Vec4::operator*=(const float tab[4][4])
{
    float x1 = this->x;
    float y1 = this->y;
    float z1 = this->z;
    float w1 = this->w;

    this->x = tab[0][0] * x1 + tab[0][1] * y1 + tab[0][2] * z1 + tab[0][3] * w1;
    this->y = tab[1][0] * x1 + tab[1][1] * y1 + tab[1][2] * z1 + tab[1][3] * w1;
    this->z = tab[2][0] * x1 + tab[2][1] * y1 + tab[2][2] * z1 + tab[2][3] * w1;
    this->w = tab[3][0] * x1 + tab[3][1] * y1 + tab[3][2] * z1 + tab[3][3] * w1;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Mat3                       /////////////////////////////////////////////////////

Mat3::Mat3(const float a[3][3])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            tab[i][j] = a[i][j];
        }
    }
}

Mat3::Mat3(const float a, const float b, const float c,
           const float d, const float e, const float f,
           const float g, const float h, const float i)
{
    tab[0][0] = a;
    tab[0][1] = b;
    tab[0][2] = c;
    tab[1][0] = d;
    tab[1][1] = e;
    tab[1][2] = f;
    tab[2][0] = g;
    tab[2][1] = h;
    tab[2][2] = i;
}

void Mat3::PrintMatrix()
{
    for (int i = 0; i < 3; i++)
    {
        printf("{ ");
        for (int j = 0; j < 2; j++)
            printf("%f, ", this->tab[i][j]);
        printf("%f }\n", this->tab[i][2]);
    }
    printf("\n\n");
}

Mat3 Mat3::GetTransposeMat3()
{
    Mat3 matrix = Mat3();
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            matrix.tab[i][j] = this->tab[j][i];
        }
    }
    return matrix;
}

Mat3 Mat3::GetAdjugateMat3()
{
    Mat3 matrix = Mat3();   

    matrix.tab[0][0] = GetDeterminantMat2(this->tab[1][1], this->tab[1][2], this->tab[2][1], this->tab[2][2]);
    matrix.tab[0][1] = GetDeterminantMat2(this->tab[1][0], this->tab[1][2], this->tab[2][0], this->tab[2][2]);
    matrix.tab[0][2] = GetDeterminantMat2(this->tab[1][0], this->tab[1][1], this->tab[2][0], this->tab[2][1]);

    matrix.tab[1][0] = GetDeterminantMat2(this->tab[0][1], this->tab[0][2], this->tab[2][1], this->tab[2][2]);
    matrix.tab[1][1] = GetDeterminantMat2(this->tab[0][0], this->tab[0][2], this->tab[2][0], this->tab[2][2]);
    matrix.tab[1][2] = GetDeterminantMat2(this->tab[0][0], this->tab[0][1], this->tab[2][0], this->tab[2][1]);

    matrix.tab[2][0] = GetDeterminantMat2(this->tab[0][1], this->tab[0][2], this->tab[1][1], this->tab[1][2]);
    matrix.tab[2][1] = GetDeterminantMat2(this->tab[0][0], this->tab[0][2], this->tab[1][0], this->tab[1][2]);
    matrix.tab[2][2] = GetDeterminantMat2(this->tab[0][0], this->tab[0][1], this->tab[1][0], this->tab[1][1]);

    return matrix;
}

Mat3 Mat3::GetInvertibleMat3()
{
    return (this->GetAdjugateMat3().GetTransposeMat3() * (1 / GetDeterminantMat3(this->tab)));
}

void Mat3::operator=(const Mat3& a)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->tab[i][j] = a.tab[i][j];
        }
    }
}


void Mat3::operator*=(const Mat3& a)
{
    Mat3 c = Mat3();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                c.tab[i][j] += this->tab[i][k] * a.tab[k][j];
            }
        }
    }

    *this = c;
}

//Working
void Mat3::operator*=(const float a)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            this->tab[i][j] *= a;
        }
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////                       Mat4                       /////////////////////////////////////////////////////

void Mat4::Translate(const Vec3& translation)
{
    printf("BEFORE:\n");
    PrintMatrix();

    this->tab[0][3] += translation.x;
    this->tab[1][3] += translation.y;
    this->tab[2][3] += translation.z;

    printf("\nAFTER:\n");
    PrintMatrix();
    printf("\n\n\n\n");
}

void Mat4::Rotate(const Vec3& rotation)
{
    printf("BEFORE:\n");
    PrintMatrix();

    if (rotation.y != 0)
        *this *= CreateYRotationMatrix(rotation.y);
    if (rotation.x != 0)
       *this *= CreateXRotationMatrix(rotation.x);
    if (rotation.z != 0)
       *this *= CreateZRotationMatrix(rotation.z);

    printf("\nAFTER:\n");
    PrintMatrix();
    printf("\n\n");
}

void Mat4::Scale(const Vec3& scale)
{
    printf("BEFORE:\n");
    PrintMatrix();

    *this *= CreateScaleMatrix(scale);

    printf("\nAFTER:\n");
    PrintMatrix();
    printf("\n\n");
}

Mat4::Mat4(const float a[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            tab[i][j] = a[i][j];
        }
    }
}

Mat4::Mat4(const float a, const float b, const float c, const float d, const float e, const float f, const float g, const float h, const float i, const float j, const float k, const float l, const float m, const float n, const float o, const float p)
{
    tab[0][0] = a;
    tab[0][1] = b;
    tab[0][2] = c;
    tab[0][3] = d;
    tab[1][0] = e;
    tab[1][1] = f;
    tab[1][2] = g;
    tab[1][3] = h;
    tab[2][0] = i;
    tab[2][1] = j;
    tab[2][2] = k;
    tab[2][3] = l;
    tab[3][0] = m;
    tab[3][1] = n;
    tab[3][2] = o;
    tab[3][3] = p;
}

void Mat4::PrintMatrix()
{
    for (int i = 0; i < 4; i++)
    {
        printf("{ ");
        for (int j = 0; j < 3; j++)
            printf("%f, ", this->tab[i][j]);
        printf("%f }\n", this->tab[i][3]);
    }
    printf("\n\n");
}

Mat4 Mat4::GetTransposeMat4()
{
    Mat4 matrix = Mat4();
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            matrix.tab[i][j] = this->tab[j][i];
        }
    }
    return matrix;
}

Mat4 Mat4::GetAdjugateMat4()
{
    Mat4 matrix = Mat4();

    matrix.tab[0][0] = GetDeterminantMat3({ this->tab[1][1], this->tab[1][2], this->tab[1][3] }, { this->tab[2][1], this->tab[2][2], this->tab[2][3] }, { this->tab[3][1], this->tab[3][2], this->tab[3][3] });
    matrix.tab[0][1] = GetDeterminantMat3({ this->tab[1][0], this->tab[1][2], this->tab[1][3] }, { this->tab[2][0], this->tab[2][2], this->tab[2][3] }, { this->tab[3][0], this->tab[3][2], this->tab[3][3] });
    matrix.tab[0][2] = GetDeterminantMat3({ this->tab[1][0], this->tab[1][1], this->tab[1][3] }, { this->tab[2][0], this->tab[2][1], this->tab[2][3] }, { this->tab[3][0], this->tab[3][1], this->tab[3][3] });
    matrix.tab[0][3] = GetDeterminantMat3({ this->tab[1][0], this->tab[1][1], this->tab[1][2] }, { this->tab[2][0], this->tab[2][1], this->tab[2][2] }, { this->tab[3][0], this->tab[3][1], this->tab[3][2] });

    matrix.tab[1][0] = GetDeterminantMat3({ this->tab[0][1], this->tab[0][2], this->tab[0][3] }, { this->tab[2][1], this->tab[2][2], this->tab[2][3] }, { this->tab[3][1], this->tab[3][2], this->tab[3][3] });
    matrix.tab[1][1] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][2], this->tab[0][3] }, { this->tab[2][0], this->tab[2][2], this->tab[2][3] }, { this->tab[3][0], this->tab[3][2], this->tab[3][3] });
    matrix.tab[1][2] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][3] }, { this->tab[2][0], this->tab[2][1], this->tab[2][3] }, { this->tab[3][0], this->tab[3][1], this->tab[3][3] });
    matrix.tab[1][3] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][2] }, { this->tab[2][0], this->tab[2][1], this->tab[2][2] }, { this->tab[3][0], this->tab[3][1], this->tab[3][2] });

    matrix.tab[2][0] = GetDeterminantMat3({ this->tab[0][1], this->tab[0][2], this->tab[0][3] }, { this->tab[1][1], this->tab[1][2], this->tab[1][3] }, { this->tab[3][1], this->tab[3][2], this->tab[3][3] });
    matrix.tab[2][1] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][2], this->tab[0][3] }, { this->tab[1][0], this->tab[1][2], this->tab[1][3] }, { this->tab[3][0], this->tab[3][2], this->tab[3][3] });
    matrix.tab[2][2] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][3] }, { this->tab[1][0], this->tab[1][1], this->tab[1][3] }, { this->tab[3][0], this->tab[3][1], this->tab[3][3] });
    matrix.tab[2][3] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][2] }, { this->tab[1][0], this->tab[1][1], this->tab[1][2] }, { this->tab[3][0], this->tab[3][1], this->tab[3][2] });

    matrix.tab[3][0] = GetDeterminantMat3({ this->tab[0][1], this->tab[0][2], this->tab[0][3] }, { this->tab[1][1], this->tab[1][2], this->tab[1][3] }, { this->tab[2][1], this->tab[2][2], this->tab[2][3] });
    matrix.tab[3][1] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][2], this->tab[0][3] }, { this->tab[1][0], this->tab[1][2], this->tab[1][3] }, { this->tab[2][0], this->tab[2][2], this->tab[2][3] });
    matrix.tab[3][2] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][3] }, { this->tab[1][0], this->tab[1][1], this->tab[1][3] }, { this->tab[2][0], this->tab[2][1], this->tab[2][3] });
    matrix.tab[3][3] = GetDeterminantMat3({ this->tab[0][0], this->tab[0][1], this->tab[0][2] }, { this->tab[1][0], this->tab[1][1], this->tab[1][2] }, { this->tab[2][0], this->tab[2][1], this->tab[2][2] });

    return matrix;
}


Mat4 Mat4::GetInvertibleMat4()
{
    return (this->GetAdjugateMat4().GetTransposeMat4() * (1 / GetDeterminantMat4(*this)));
}


float GetDeterminantMat2(const float a, const float b, const float c, const float d)
{
    return (a * d - b * c);
}

float GetDeterminantMat3(const Vec3& a, const Vec3& b, const Vec3& c)
{
    return (
        a.x * GetDeterminantMat2(b.y, b.z, c.y, c.z)
        - a.y * GetDeterminantMat2(b.x, b.z, c.x, c.z)
        + a.z * GetDeterminantMat2(b.x, b.y, c.x, c.y)
        );
}

float GetDeterminantMat3(const float tab[3][3])
{
    return (
        tab[0][0] * GetDeterminantMat2(tab[1][1], tab[1][2], tab[2][1], tab[2][2])
        - tab[0][1] * GetDeterminantMat2(tab[1][0], tab[1][2], tab[2][0], tab[2][2])
        + tab[0][2] * GetDeterminantMat2(tab[1][0], tab[1][1], tab[2][0], tab[2][1])
        );
}

float GetDeterminantMat4(const Mat4& a)
{
    return(
        a.tab[0][0] * GetDeterminantMat3({ a.tab[1][1], a.tab[1][2], a.tab[1][3] }, { a.tab[2][1], a.tab[2][2], a.tab[2][3] }, { a.tab[3][1], a.tab[3][2], a.tab[3][3] })
        - a.tab[0][1] * GetDeterminantMat3({ a.tab[1][0], a.tab[1][2], a.tab[1][3] }, { a.tab[2][0], a.tab[2][2], a.tab[2][3] }, { a.tab[3][0], a.tab[3][2], a.tab[3][3] })
        + a.tab[0][2] * GetDeterminantMat3({ a.tab[1][0], a.tab[1][1], a.tab[1][3] }, { a.tab[2][0], a.tab[2][1], a.tab[2][3] }, { a.tab[3][0], a.tab[3][1], a.tab[3][3] })
        - a.tab[0][3] * GetDeterminantMat3({ a.tab[1][0], a.tab[1][1], a.tab[1][2] }, { a.tab[2][0], a.tab[2][1], a.tab[2][2] }, { a.tab[3][0], a.tab[3][1], a.tab[3][2] })
        );
}




void Mat4::operator=(const Mat4& a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->tab[i][j] = a.tab[i][j];
        }
    }
}


void Mat4::operator*=(const Mat4& a)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                c.tab[i][j] += this->tab[i][k] * a.tab[k][j];
            }
        }
    }

    *this = c;
}

//Working
void Mat4::operator*=(const float a)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            this->tab[i][j] *= a;
        }
    }
}

///////////////////////////////////                       Mat4                       /////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Mat4 operator*(const Mat4& a, const Mat4& b)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                c.tab[i][j] += a.tab[i][k] * b.tab[k][j];
            }
        }
    }

    return c;
}


Mat4 operator*(const Mat4& a, const float b)
{
    Mat4 c = Mat4();

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            c.tab[i][j] = a.tab[i][j] * b;
        }
    }

    return c;
}

Mat3 operator*(const Mat3& a, const Mat3& b)
{
    Mat3 c = Mat3();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                c.tab[i][j] += a.tab[i][k] * b.tab[k][j];
            }
        }
    }

    return c;
}

Mat3 operator*(const Mat3& a, const float b)
{
    Mat3 c = Mat3();

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            c.tab[i][j] = a.tab[i][j] * b;
        }
    }

    return c;
}


Vec4 operator*(const Mat4& a, const Vec4& b)
{
    Vec4 c = Vec4();

    c.x = a.tab[0][0] * b.x + a.tab[0][1] * b.y + a.tab[0][2] * b.z + a.tab[0][3] * b.w;
    c.y = a.tab[1][0] * b.x + a.tab[1][1] * b.y + a.tab[1][2] * b.z + a.tab[1][3] * b.w;
    c.z = a.tab[2][0] * b.x + a.tab[2][1] * b.y + a.tab[2][2] * b.z + a.tab[2][3] * b.w;
    c.w = a.tab[3][0] * b.x + a.tab[3][1] * b.y + a.tab[3][2] * b.z + a.tab[3][3] * b.w;

    return c;
}

Vec4 operator*(const Vec4& b, const Mat4& a)
{
    Vec4 c = Vec4();

    c.x = a.tab[0][0] * b.x + a.tab[0][1] * b.y + a.tab[0][2] * b.z + a.tab[0][3] * b.w;
    c.y = a.tab[1][0] * b.x + a.tab[1][1] * b.y + a.tab[1][2] * b.z + a.tab[1][3] * b.w;
    c.z = a.tab[2][0] * b.x + a.tab[2][1] * b.y + a.tab[2][2] * b.z + a.tab[2][3] * b.w;
    c.w = a.tab[3][0] * b.x + a.tab[3][1] * b.y + a.tab[3][2] * b.z + a.tab[3][3] * b.w;

    return c;
}

float GetMaximumDifference(const float a, const float b, const float c)
{
    float maxDiff = 0;
    float tab[6] = { a - b, a - c, b - a, b - c, c - a, c - b };
    for (int i = 0; i < 6; i++)
    {
        if (tab[i] > maxDiff)
            maxDiff = tab[i];
    }
    return maxDiff;
}
