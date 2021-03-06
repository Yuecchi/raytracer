#include <cmath>

#include "Triangle.hpp"
#include "Math.hpp"

void Triangle::computeNormal() {
    glm::vec3 u = m_p2 - m_p1;
    glm::vec3 v = m_p3 - m_p1;
    m_normal = normalize(glm::cross(v, u));
}

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, Material material) {
    m_p1 = p1;
    m_p2 = p2;
    m_p3 = p3;
    m_material = material;
    computeNormal();
}

/**
 * Moller-Trumbore triangle interseaction algorithim, taken from:
 * https://en.wikipedia.org/wiki/Möller–Trumbore_intersection_algorithm
 */ 

RayIntersectData Triangle::rayIntersect(Ray ray) {
	RayIntersectData result = {
		nullptr, INFINITY
	};
    static const float bias = 1e-7;
    glm::vec3 e1 = m_p2 - m_p1;
    glm::vec3 e2 = m_p3 - m_p1;
    
    glm::vec3 h  = glm::cross(ray.direction(), e2);
    float a = glm::dot(e1, h);
    if (a > -bias && a < bias) {
        return result; // the ray is parallel to the triangle
    }

    float f = 1.0f / a;
    glm::vec3 s = ray.origin() - m_p1;
    float u = f * glm::dot(s, h);
    if (u < 0.0f || u > 1.0f) {
        return result;
    }

    glm::vec3 q = glm::cross(s, e1);
    float v = f * glm::dot(ray.direction(), q);
    if (v < 0.0f || (u + v) > 1.0f) {
        return result;
    }

    float t = f * glm::dot(e2, q);
    if (t > bias) {
        result.distance = t;
        result.sceneObject = this;
        return result;
    }
    else return result;
}

glm::vec3 Triangle::normal(const glm::vec3 &v) {
    return m_normal;
}

glm::vec3 &Triangle::p1() {
    return m_p1;
}

glm::vec3 &Triangle::p2() {
    return m_p2;
}

glm::vec3 &Triangle::p3() {
    return m_p3;
}

Triangle::~Triangle() = default;