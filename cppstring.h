#include <cctype>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <type_traits>

/*!
 *  @class String
 *
 *  @brief A custom String implementation
 *
 *  A custom C++ implementation of a String object for pedagogical purposes.
 *  Is efficient for specifying the Length of your String and does not depend
 *  on the use of a NULL termination.
 *
 *  @invariant String data will always point to NULL or a valid address.
 *  @invariant String Length will always indicate amount of allocated space.
 */

class String {
    char *       m_data_;    /*!< The ASCII characters that comprise the String */
    std::size_t  m_length_;  /*!< The number of characters allocated in data */
    std::size_t  m_capacity_;

public:

    /*!
     *  @brief Empty String Constructor.
     *  @post String Length is set equal to 0.
     */
    String();

    /*!
     *  @brief Single-character String Constructor.
     *  @param[in] c A char literal.
     *  @post String data equals @a c and String Length equals 1.
     */
    explicit String(char c);

    /*!
     *  @brief char* String Constructor
     *  @param[in] c A char* null-terminated string.
     *  @post String Length equals @code{.cpp}Strlen(c)@endcode.
     *  @post String data equals @a c allocated values, except the null-terminator.
     */
    explicit String(const char * c_string);

    /*!
     *  @brief Copy String Constructor
     *  @param[in] s A String instance.
     *  @post This String will be identical to String @a s.
     */
    String(const String & other);

    /*!
     *  @brief Move String Constructor
     *  @param[in] s A String instance.
     *  @post This String will be moved from String @a other.
     */
    String(String && other);

    /*!
     *  @brief Default String Destructor
     *  @post String data is deleted.
     */
    ~String();

    /*!
     *  @brief Swap two Strings.
     *  @param[in] s A String instance.
     *  @post This String will be swaped with String @a other.
     */
    void Swap(String & other);

    /*!
     *  @brief String Length.
     *  @return Value in String @c Length.
     */
    std::size_t Length() const;

    /*!
     *  @brief String Index of @a c.
     *  @param[in] c A char literal.
     *  @return The Index of @a c in String, if exists; -1 otherwise.
     */
    std::int64_t Index(char c) const;

    /*!
     *  @brief Converts lowercase alphabetic characters to uppercase.
     *  @param[in] first Starting Index of String to change case.
     *  @param[in] last  Ending Index of String to change case.
     *  @pre @a first is less than or equal to @a last and @a last is less than
     *       or equal to String Length.
     *  @post All lowercase alphabetic characters in String data greater than
     *        or equal to @a first, but less than @a last are uppercase.
     */
    void ToUpper(std::size_t first, std::size_t last);

    /*!
     *  @brief Converts uppercase alphabetic characters to lowercase.
     *  @param[in] first Starting Index of String to change case.
     *  @param[in] last Ending Index of String to change case.
     *  @pre @a first is less than or equal to @a last and @a last is less than
     *       or equal to String Length.
     *  @post All uppercase alphabetic characters in String data greater than
     *        or equal to @a first, but less than @a last are lowercase.
     */
    void ToLower(std::size_t first, std::size_t last);

    //@{
    /*!
     *  @brief Stream operators.
     *  @param so A stream object.
     *  @param s  A String object.
     *  @return Stream object containing String content.
     */
    friend std::ostream & operator<< (std::ostream & stream, const String & string);
    friend std::istream & operator>> (std::istream & stream, String & string);
    //@}

    //@{
    /*!
     *  @brief Access String character.
     *  @param j Index value in String.
     *  @pre @a j is less than String Length.
     *  @return character at @a j Index of String data.
     *  @throw int
     */
    char   operator[] (std::size_t Index) const;
    char & operator[] (std::size_t Index);
    //@}

    /*!
     *  @brief Sets String value.
     *  @param[in] s A String object.
     *  @return A String reference to *this.
     *  @post String will be equivalent to @a s.
     */
    String & operator= (const String & other);

    /*!
     *  @brief Moves String value.
     *  @param[in] other A String object.
     *  @return A String reference to *this.
     *  @post String will be moved from @a other.
     */
    String & operator= (String && other);

    /*!
     *  @brief Append to String.
     *  @param[in] s A String object.
     *  @return A String reference to *this.
     *  @post String will equal the concatenation of itself with @a s.
     */
    String & operator+= (const String & other);

    //@{
    /*!
     *  @brief String concatenation (addition).
     *  @param[in] lhs The left-hand operand String or String convertable.
     *  @param[in] rhs The right-hand operand String or String convertable.
     *  @return Copy of a String object.
     *  @post The String will be the concatenation of @a lhs and @a rhs.
     */
    friend String operator+ (const String & lhs, const String & rhs);


    // friend String operator+ (String &&      lhs, String &&      rhs);
    // friend String operator+ (String &&      lhs, const String & rhs);
    // friend String operator+ (String &&      lhs, char           rhs);
    // friend String operator+ (String &&      lhs, const char *   rhs);
    // friend String operator+ (char           lhs, String &&      rhs);
    // friend String operator+ (const char *   lhs, String &&      rhs);
    // friend String operator+ (const String & lhs, String &&      rhs);

    //@}

    //@{
    /*!
     *  @brief String equality
     *  @param[in] lhs The left-hand operand String or String convertable.
     *  @param[in] rhs The right-hand operand String or String convertable.
     *  @return True, if @a lhs and @a rhs have the same Length, and each
     *          character in their String data are identical in both value
     *          and Index.
     */
    friend bool operator== (const String & lhs, const String & rhs);
    friend bool operator== (const String & lhs, char           rhs);
    friend bool operator== (const String & lhs, const char *   rhs);
    friend bool operator== (char           lhs, const String & rhs);
    friend bool operator== (const char *   lhs, const String & rhs);
    //@}

    //@{
    /*!
     *  @brief String inequality: Greater-than.
     *  @param[in] lhs The left-hand operand String or String convertable.
     *  @param[in] rhs The right-hand operand String or String convertable.
     *  @return True, if @a lhs is in dictionary order (Capitals-first) to
     *          @a rhs when comparing alphabetical characters or @a lhs is
     *          greater in ASCII value to @a rhs, in corresponding String
     *          data indices.
     */
    friend bool operator> (const String & lhs, const String & rhs);
    friend bool operator> (const String & lhs, char           rhs);
    friend bool operator> (const String & lhs, const char *   rhs);
    friend bool operator> (char           lhs, const String & rhs);
    friend bool operator> (const char *   lhs, const String & rhs);
    //@}

    //@{
    /*!
     *  @brief String non-equality
     *  @param[in] lhs The left-hand operand String or String convertable.
     *  @param[in] rhs The right-hand operand String or String convertable.
     *  @return True, if @a lhs is not equal to @a rhs.
     *  @see String::operator==
     */
    friend bool operator!= (const String & lhs, const String & rhs);
    friend bool operator!= (const String & lhs, char           rhs);
    friend bool operator!= (const String & lhs, const char *   rhs);
    friend bool operator!= (char           lhs, const String & rhs);
    friend bool operator!= (const char *   lhs, const String & rhs);
    //@}

    //@{
    /*!
     *  @brief String inequality: Less-than.
     *  @param[in] lhs The left-hand operand String or String convertable.
     *  @param[in] rhs The right-hand operand String or String convertable.
     *  @return True, if @a lhs is neither equal to, nor greater-than @a rhs.
     *  @see String::operator==,String::operator>
     */
    friend bool operator< (const String & lhs, const String & rhs);
    friend bool operator< (const String & lhs, char           rhs);
    friend bool operator< (const String & lhs, const char *   rhs);
    friend bool operator< (char           lhs, const String & rhs);
    friend bool operator< (const char *   lhs, const String & rhs);
    //@}

    //@{
    /*!
     *  @brief String inequality: Less-than or equal
     *  @param[in] lhs The left-hand operand String or String convertable.
     *  @param[in] rhs The right-hand operand String or String convertable.
     *  @return True, if @a lhs is not greater-than @a rhs.
     *  @see String::operator>
     */
    friend bool operator<= (const String & lhs, const String & rhs);
    friend bool operator<= (const String & lhs, char           rhs);
    friend bool operator<= (const String & lhs, const char *   rhs);
    friend bool operator<= (char           lhs, const String & rhs);
    friend bool operator<= (const char *   lhs, const String & rhs);
    //@}

    //@{
    /*!
     *  @brief String inequality: Greater-than or equal
     *  @param[in] lhs The left-hand operand String or String convertable.
     *  @param[in] rhs The right-hand operand String or String convertable.
     *  @return True, if @a lhs is greater-than or equal to @a rhs.
     *  @see String::operator>,String::operator==
     */
    friend bool operator>= (const String & lhs, const String & rhs);
    friend bool operator>= (const String & lhs, char           rhs);
    friend bool operator>= (const String & lhs, const char *   rhs);
    friend bool operator>= (char           lhs, const String & rhs);
    friend bool operator>= (const char *   lhs, const String & rhs);
    //@}
private:
    static std::size_t Strlen(const char *c_string);
    void Clear();
    void PushBack(char c);
    void IncreaseData();
};