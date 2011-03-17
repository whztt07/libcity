/**
 * This code is part of libcity library.
 *
 * @file streetgraph/intersection.h
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for road representation
 *
 */

#ifndef _ROAD_H_
#define _ROAD_H_

class Line;
class Intersection;

class Road
{
  private:
    Road();

  public:
    /** Create road between two intersections.
        Path is determined automaticaly.*/
    Road(Intersection *first, Intersection *second);
    virtual ~Road();

    Intersection* begining() const;
    Intersection* end() const;

    void setBegining(Intersection* intersection);
    void setEnd(Intersection* intersection);

    Line* path() const;

    void setPath(Line& roadPath) throw();

  private:
    /* Topological information */
    Intersection* from; /**< Where the road starts. */
    Intersection* to;   /**< Where it leads to. */

    /* Geometrical information */
    Line* geometrical_path; /**< Path that the road takes between the two topological points */

    void estimatePath();
};

/* Inlines */

inline Intersection* Road::begining() const
{
  return from;
}

inline Intersection* Road::end() const
{
  return to;
}

inline void Road::setBegining(Intersection* intersection)
{
  from = intersection;
}

inline void Road::setEnd(Intersection* intersection)
{
  to = intersection;
}

inline Line* Road::path() const
{
  return geometrical_path;
}


#endif