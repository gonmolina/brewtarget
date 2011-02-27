/*
 * fermentable.h is part of Brewtarget, and is Copyright Philip G. Lee
 * (rocketman768@gmail.com), 2009.
 *
 * Brewtarget is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * Brewtarget is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _FERMENTABLE_H
#define _FERMENTABLE_H

#include <string>
#include <exception>
#include "observable.h"
#include <QDomNode>
#include "BeerXMLElement.h"
#include <QStringList>
#include <QString>

class Fermentable;

class Fermentable : public Observable, public BeerXMLElement
{
   friend class Brewtarget;
public:

   //! These should exactly correspond to \b types.
   enum Type { TYPEGRAIN=0, TYPESUGAR, TYPEEXTRACT, TYPEDRY_EXTRACT, TYPEADJUNCT, NUMTYPES };

   Fermentable();
   Fermentable( Fermentable& other );
   Fermentable(const QDomNode& fermentableNode);
   
   virtual void fromNode(const QDomNode& node); // From BeerXMLElement
   virtual void toXml(QDomDocument& doc, QDomNode& parent); // From BeerXMLElement

   // Operators
   friend bool operator<(Fermentable &f1, Fermentable &f2);
   friend bool operator==(Fermentable &f1, Fermentable &f2);

   //! Info for hasChanged(). Never use the \b DONOTUSE ok?
   enum{ DONOTUSE, NAME, TYPE, AMOUNT, YIELD, COLOR, AFTERBOIL, ORIGIN, SUPPLIER, NOTES, COARSEFINEDIFF, MOISTURE,
         DIASTATICPOWER, PROTEIN, MAXINBATCH, ISMASHED };
   
   // Get
   const QString getName() const;
   int getVersion() const;
   const Type getType() const;
   const QString getTypeString() const;
   //! Returns a translated type string.
   const QString getTypeStringTr() const;
   double getAmount_kg() const;
   double getYield_pct() const;
   double getColor_srm() const;
   
   bool getAddAfterBoil() const;
   const QString getOrigin() const;
   const QString getSupplier() const;
   const QString getNotes() const;
   double getCoarseFineDiff_pct() const;
   double getMoisture_pct() const;
   double getDiastaticPower_lintner() const;
   double getProtein_pct() const;
   double getMaxInBatch_pct() const;
   bool getRecommendMash() const;
   double getIbuGalPerLb() const;

   // Derived getters...

   // Get the maximum kg of equivalent sucrose that will come out of this ferm.
   double getEquivSucrose_kg() const;

   // Set
   void setName( const QString& str );
   void setVersion( int num );
   void setType( Type t );
   void setAmount_kg( double num );
   void setYield_pct( double num );
   void setColor_srm( double num );
   
   void setAddAfterBoil( bool b );
   void setOrigin( const QString& str );
   void setSupplier( const QString& str);
   void setNotes( const QString& str );
   void setCoarseFineDiff_pct( double num );
   void setMoisture_pct( double num );
   void setDiastaticPower_lintner( double num );
   void setProtein_pct( double num );
   void setMaxInBatch_pct( double num );
   void setRecommendMash( bool b );
   void setIbuGalPerLb( double num );
   
   /*** My extensions ***/
   bool getIsMashed() const;
   void setIsMashed(bool var);
   /*** END my extensions ***/
   
private:
   QString name;
   static const int version = 1;
   Type type;
   double amount_kg;
   double yield_pct;
   double color_srm;

   bool addAfterBoil;
   QString origin;
   QString supplier;
   QString notes;
   double coarseFineDiff_pct;
   double moisture_pct;
   double diastaticPower_lintner;
   double protein_pct;
   double maxInBatch_pct;
   bool recommendMash;
   double ibuGalPerLb;
   /*** My extensions ***/
   bool isMashed;
   /*** END my extensions ***/

   static bool isValidType( const QString& str );
   void setDefaults();

   static QStringList types;
};

inline bool FermentablePtrLt( Fermentable* lhs, Fermentable* rhs)
{
   return *lhs < *rhs;
}

inline bool FermentablePtrEq( Fermentable* lhs, Fermentable* rhs)
{
   return *lhs == *rhs;
}

struct Fermentable_ptr_cmp
{
   bool operator()( Fermentable* lhs, Fermentable* rhs)
   {
      return *lhs < *rhs;
   }
};

struct Fermentable_ptr_equals
{
   bool operator()( Fermentable* lhs, Fermentable* rhs )
   {
      return *lhs == *rhs;
   }
};

#endif
