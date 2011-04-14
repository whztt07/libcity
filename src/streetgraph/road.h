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
class Path;

class Road
{
  public:
    /** Create road between two intersections.
        Path is determined automaticaly.*/
    Road();
    Road(Intersection *first, Intersection *second);

    /**
     * Create just path of the road.
     **/
    Road(Path const& path);
    virtual ~Road();

    Intersection* begining() const;
    Intersection* end() const;

    void setBegining(Intersection* intersection);
    void setEnd(Intersection* intersection);

    Path* path() const;
    void setPath(Path const& roadPath) throw();

    enum types
    {
      PRIMARY_ROAD,
      SECONDARY_ROAD
    };

    virtual types type();
    void setType(types type);

  private:
    /* Topological information */
    Intersection* from; /**< Where the road starts. */
    Intersection* to;   /**< Where it leads to. */

    /* Geometrical information */
    Path* geometrical_path; /**< Path that the road takes between the two topological points */

    types roadType;

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


#endif
