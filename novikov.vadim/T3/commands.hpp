#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <unordered_map>
#include <functional>
#include <iomanip>
#include <formatGuard.hpp>
#include "polygon.hpp"
#include "predicates.hpp"

namespace novikov
{
  namespace cmd
  {
    using poly_vec_t = std::vector< Polygon >;

    enum EmptyVectors
    {
      Disabled,
      Enabled
    };

    struct AccumulateArea
    {
      std::function< double(double, const Polygon& rhs) > func;
      EmptyVectors empty_vector_support;
      double operator()(double val, const Polygon& rhs);
    };

    using area_args_t = std::unordered_map< std::string, AccumulateArea >;
    void area(const area_args_t& cmds, const poly_vec_t& vec, std::istream& in, std::ostream& out);

    using predicate_t = std::function< bool(const Polygon&) >;
    double accAreaIf(double val, const Polygon& rhs, predicate_t pred);
    double accAreaMean(double val, const Polygon& rhs, std::size_t size);

    using poly_vec_it_t = poly_vec_t::const_iterator;
    using comparator_t = std::function< bool(const Polygon&, const Polygon&) >;
    struct Max
    {
      poly_vec_it_t operator()(poly_vec_it_t begin, poly_vec_it_t end, comparator_t comp);
    };
    struct Min
    {
      poly_vec_it_t operator()(poly_vec_it_t begin, poly_vec_it_t end, comparator_t comp);
    };
    using minmax_args_t = std::unordered_map< std::string, std::function< void(const std::vector< Polygon >&, std::ostream&) > >;
    void minmax(const minmax_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out);
    template< typename FindTheMost >
    void minmaxArea(const poly_vec_t& vec, std::ostream& out)
    {
      FormatGuard guard(out);
      auto res = FindTheMost()(vec.cbegin(), vec.cend(), compareAreas);
      out << std::setprecision(1) << std::fixed;
      out << getArea(*res) << "\n";
    }
    template< typename FindTheMost >
    void minmaxVertexes(const poly_vec_t& vec, std::ostream& out)
    {
      FormatGuard guard(out);
      auto res = FindTheMost()(vec.cbegin(), vec.cend(), compareVertexes);
      out << res->points.size() << "\n";
    }

    using count_args_t = std::unordered_map< std::string, std::function< bool(const Polygon&) > >;
    void count(const count_args_t& args, const poly_vec_t& vec, std::istream& in, std::ostream& out);

    struct EntryDuplicator
    {
      poly_vec_t& vec;
      const Polygon& arg;
      Polygon operator()(Polygon&& rhs);
    };
    void echo(poly_vec_t& vec, std::istream& in, std::ostream& out);

    void inFrame(const poly_vec_t& vec, std::istream& in, std::ostream& out);
    Polygon getFrameRect(const poly_vec_t& vec);
  }
}

#endif
