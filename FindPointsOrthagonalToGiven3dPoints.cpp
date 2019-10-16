#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cmath>

std::vector<float> normalize(std::vector<float> &toNormalize);

std::vector<float> CalculateOrthogonalVector (const std::vector<float> &roadVector, 
    const std::vector<float> &startingPoint);

std::vector<float> CalculatePointOnOrthogonalVector_x_DistanceAway 
    (const std::vector<float> &pointOfOrigin, const std::vector<float> &directionVector, 
    const float &distanceAway); 

int main ()
{
    // Example values - change at your pleasure for testing purposes
    std::vector<float> N1, N2;
    N1 = {1, 1, 1 };
    N2 = {3, 3, 3};

    std::vector<float> roadVector (N1.size(), 0); 

    std::transform(N1.begin(), N1.end(), N2.begin(), roadVector.begin(), 
        std::minus<float>());

    std::vector<float> orthogonalVector = CalculateOrthogonalVector(roadVector, N1);

    normalize(orthogonalVector);

    std::vector<float> orthogonalPoint1 = 
        CalculatePointOnOrthogonalVector_x_DistanceAway(N1, orthogonalVector, 50);
    std::vector<float> orthogonalPoint2 =
        CalculatePointOnOrthogonalVector_x_DistanceAway(N1, orthogonalVector, -50);

    for (auto value : orthogonalPoint1)
    {
        std::cout << value << " ";
    }

    std::cout << "\n";

    for (auto value : orthogonalPoint2)
    {
        std::cout << value << " ";
    }
}

// Function to normalize a vector

std::vector<float> normalize(std::vector<float> &toNormalize)
{
    float magnitude; 
    for (float value : toNormalize)
    {
        magnitude += value * value; 
    }

    magnitude = std::sqrt(magnitude);

    for (int i = 0; i < toNormalize.size(); i++)
    {
        toNormalize[i] = toNormalize[i] / magnitude; 
    }

    return toNormalize;
}

// Keeping orthogonal vector with same z value as N1, calculate a vector orthoganal 
// to road
// Set dot product between unknown vector and road to 0 and solve for x and y values
// of unknown vector
// Assume a value for y of the orthogonal vector - we know z will be same as N1's z

std::vector<float> CalculateOrthogonalVector (const std::vector<float> &roadVector, 
    const std::vector<float> &startingPoint)
{
    float orthogonalVecY = 1; 

    float orthogonalVecX = (-roadVector[2] * startingPoint[2] - 
        roadVector[1] * orthogonalVecY) / roadVector[0];

    std::vector<float> orthogonalVector {orthogonalVecX, orthogonalVecY, startingPoint[2] };

    return orthogonalVector; 
}

// Calculate the location of a point X distance away from a given point along
// a specified direction vector

std::vector<float> CalculatePointOnOrthogonalVector_x_DistanceAway 
    (const std::vector<float> &pointOfOrigin, const std::vector<float> &directionVector, 
    const float &distanceAway)

{
    std::vector<float> scaledDirectionVector (directionVector.size(), 0);
    std::vector<float> orthogonalPoint (pointOfOrigin.size(), 0); 

    std::transform(directionVector.begin(), directionVector.end(), 
        scaledDirectionVector.begin(), std::bind(std::multiplies<float>(), 
        std::placeholders::_1, distanceAway));

    std::transform(pointOfOrigin.begin(), pointOfOrigin.end(), scaledDirectionVector.begin(), 
        orthogonalPoint.begin(), std::plus<float>());

    return orthogonalPoint;
}