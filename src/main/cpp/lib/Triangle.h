#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include <cstddef>
#include <vector>
#include <cassert>

/** Triangle stores sets who have a size equal to their their index + 1.
 * The total storage of a Triangle instance is equal to the dim-th triangular
 * number (starting with T_1 = 1).
 * 0:       Elem00
 * 1:    Elem10 Elem11
 * 2: Elem20 Elem21 Elem22
 *            ...
 *
 * @brief Triangular set storage
 *
 * @author beyss
 * @date 23.08.2017
 */
template<typename T, size_t dim>
  class Triangle
  {
  private:
    /** The storage vector, 2-dimensional Triangle
     * is reduced to a 1-dimensional form.
     */
    typename std::vector<T> m_data;
  public:
    /** Creates a Triangle with an empty storage.
     */
    Triangle () :
	m_data (dim * (dim + 1) / 2, T ())
    {
    }

    /** Creates a Triangle from a given data vector whose
     * size must be the dim-th triangular number.
     *
     * @param data the data vector
     */
    Triangle (const std::vector<T> data) :
	m_data (data)
    {
      assert(m_data.size () == dim * (dim + 1) / 2);
    }

    virtual
    ~Triangle ()
    {
    }

    /** Readonly access function for the j-th element
     * of the i-th set.
     *
     * @param i the "row"
     * @param j the "column"
     * @return a constant reference to the storage element
     */
    const T&
    at (size_t i, size_t j) const
    {
      assert(i < dim);
      assert(j <= i);
      return m_data.at (i * (i + 1) / 2 + j);
    }

    /** Access function for the j-th element of the
     * i-th set.
     *
     * @param i the "row"
     * @param j the "column"
     * @return a reference to the storage element
     */
    T&
    at (size_t i, size_t j)
    {
      assert(i < dim);
      assert(j <= i);
      return m_data.at (i * (i + 1) / 2 + j);
    }
  };

#endif /* TRIANGLE_H_ */
