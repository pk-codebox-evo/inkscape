#ifndef SEEN_DISPLAY_CURVE_H
#define SEEN_DISPLAY_CURVE_H

/** \file
 * Wrapper around an array of NArtBpath objects.
 *
 * Author:
 *   Lauris Kaplinski <lauris@kaplinski.com>
 *
 * Copyright (C) 2000 Lauris Kaplinski
 * Copyright (C) 2000-2001 Ximian, Inc.
 * Copyright (C) 2002 Lauris Kaplinski
 * Copyright (C) 2008 Johan Engelen
 *
 * Released under GNU GPL
 */

#include <glib/gtypes.h>
#include <glib/gslist.h>

#include <2geom/forward.h>

#include "libnr/nr-forward.h"

#define SP_CURVE_LENSTEP 32

struct SPObject;

/// Wrapper around Geom::PathVector.
class SPCurve {
public:
    /* Constructors */
    explicit SPCurve(guint length = SP_CURVE_LENSTEP);
    explicit SPCurve(Geom::PathVector const& pathv);
    static SPCurve * new_from_rect(Geom::Rect const &rect);

    virtual ~SPCurve();

    void set_pathvector(Geom::PathVector const & new_pathv);
    NArtBpath const * get_bpath() const;
    Geom::PathVector const & get_pathvector() const;

    guint get_segment_count() const;
    guint nodes_in_path() const;

    SPCurve * ref();
    SPCurve * unref();

    SPCurve * copy() const;

    GSList * split() const;
    void transform(NR::Matrix const &m);
    void transform(Geom::Matrix const &m);
    void stretch_endpoints(NR::Point const &, NR::Point const &);
    void move_endpoints(NR::Point const &, NR::Point const &);
    void last_point_additive_move(Geom::Point const & p);

    void reset();

    void moveto(Geom::Point const &p);
    void moveto(NR::Point const &p);
    void moveto(gdouble x, gdouble y);
    void lineto(Geom::Point const &p);
    void lineto(NR::Point const &p);
    void lineto(gdouble x, gdouble y);
    void curveto(Geom::Point const &p0, Geom::Point const &p1, Geom::Point const &p2);
    void curveto(NR::Point const &p0, NR::Point const &p1, NR::Point const &p2);
    void curveto(gdouble x0, gdouble y0, gdouble x1, gdouble y1, gdouble x2, gdouble y2);
    void closepath();
    void closepath_current();

    SPCurve * append_continuous(SPCurve const *c1, gdouble tolerance);

    bool is_empty() const;
    bool is_closed() const;
    Geom::Curve const * last_segment() const;
    Geom::Path const * last_path() const;
    Geom::Curve const * first_segment() const;
    Geom::Path const * first_path() const;
    NR::Point first_point() const;
    NR::Point last_point() const;
    NR::Point second_point() const;
    NR::Point penultimate_point() const;

    void append(SPCurve const *curve2, bool use_lineto);
    SPCurve * create_reverse() const;
    void backspace();

    static SPCurve * concat(GSList const *list);

protected:
    gint _refcount;

    Geom::PathVector _pathv;

private:
    // Don't implement these:
    SPCurve(const SPCurve&);
    SPCurve& operator=(const SPCurve&);
};

#endif /* !SEEN_DISPLAY_CURVE_H */

/*
  Local Variables:
  mode:c++
  c-file-style:"stroustrup"
  c-file-offsets:((innamespace . 0)(inline-open . 0)(case-label . +))
  indent-tabs-mode:nil
  fill-column:99
  End:
*/
// vim: filetype=cpp:expandtab:shiftwidth=4:tabstop=8:softtabstop=4:encoding=utf-8:textwidth=99 :
