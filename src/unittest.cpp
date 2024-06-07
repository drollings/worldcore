// Twine engine .cpp

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include "base.hpp"
#include "worlds.hpp"
#include "gurpsskills.hpp"
#include "coord.hpp"
#include "editing.hpp"
#include "things.hpp"
#include "properties.hpp"
#include "Templates/sorted_node_vector.hpp"

#include <boost/random/mersenne_twister.hpp>

#include <iostream>

using namespace std;
using namespace Base;
using namespace Things;
using namespace Worlds;


void PrintProximityList(ElementList *list)
{
	ElementList::iterator	i;
	Element *e;

	if (list) {
		cout << "List is there." << endl;
		i = list->begin();
		while (i != list->end()) {
			e = *i;
			cout << e << ", ";
			++i;
		}
		cout << endl;
	} else {
		cout << "List is null." << endl;
	}
}

int TestToFrom(void)
{
	Things::Thing t("Thingie");
	Worlds::World	w;
	Worlds::Location l1, l2, l3;
	Thing t1;
	ElementList *list;

	PrintProximityList(w.GetElementsInProximity(proximityInside));
	PrintProximityList(w.GetElementsInProximity(proximityPeople));

	l1.To(w);
	l2.To(w);
	l3.To(w);
	// t1.To(w, proximityPeople);

	PrintProximityList(w.GetElementsInProximity(proximityInside));
	PrintProximityList(w.GetElementsInProximity(proximityPeople));

	l1.From();

	PrintProximityList(w.GetElementsInProximity(proximityInside));
	PrintProximityList(w.GetElementsInProximity(proximityPeople));

	l2.From();
	l3.From();

	PrintProximityList(w.GetElementsInProximity(proximityInside));
	PrintProximityList(w.GetElementsInProximity(proximityPeople));

	return EXIT_SUCCESS;
}

typedef struct
{
	UInt32		first;
	UInt32		second;
} allele;
// typedef Flags	allele;

void MakeAllele(allele &a, allele &b, allele &offspring, Flags randx)
{
	switch (randx % 4) {
	case 0:
		offspring.first = a.first;
		offspring.second = a.second;
		break;
	case 1:
		offspring.first = a.first | b.first;
		offspring.second = a.second;
		break;
	case 2:
		offspring.first = a.first;
		offspring.second = a.second | b.second;
		break;
	case 3:
		offspring.first = b.first;
		offspring.second = b.second;
	}
}

inline void PrintBits(const Flags &n)
{
	for (int i = 31; i >= 0; --i) {
		if (n & (1 << i)) 	{	cout << '1';	}
		else				{	cout << '0';	}
	}
}

inline void PrintAllele(const allele &c)
{
	PrintBits(c.first); cout << ':'; PrintBits(c.second);
}


int TestAllele(void)
{
	allele	a, b, c;
	UInt16 arr[4] = { 0, 1, 2, 3 };
	int i;
	
	a.first = 4 | (1 << 21);
	a.second = 0;
	b.first = 0;
	b.second = 2 | (1 << 22);

	cout << "a: "; PrintAllele(a); cout << endl;
	cout << "b: "; PrintAllele(b); cout << endl;

	for (i = 0; i < 4; ++i) {
		MakeAllele(a, b, c, arr[i]);
		cout << "c: "; PrintAllele(c); cout << endl;
	}
	return 1;
}


ostream& operator << (ostream& os, coord &c)
{
	os <<	"(CART) [" << c.vars.x << ':' << c.vars.y << ':' << c.vars.z << ']';
	return os;
}

ostream& operator << (ostream& os, coordSphere &c)
{
	os <<	"(SPHR) [" << c.vars.radius << ':' << c.vars.theta << ':' << c.vars.phi << ']';
	return os;
}

int TestSingleCoord(void)
{
	coordSphere a, a2, b, b2, c, c2;
	
	// a.meters = 100;
	// b.meters = 200;
	// b.theta = -5;
	a.vars.radius = 100;

	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl;

	if (a < b)	{	cout << "(a < b)" << endl;	}
	if (a > b)	{	cout << "(a > b)" << endl;	}
	if (a >= b)	{	cout << "(a >= b)" << endl;	}
	if (a <= b)	{	cout << "(a <= b)" << endl;	}
	if (a == b)	{	cout << "(a == b)" << endl;	}
	if (a != b)	{	cout << "(a != b)" << endl;	}

	a2.vars.radius = 50;
	a2.vars.theta = 0;
	a2.vars.phi = 45;

	return 1;
}


int RandomTestCoord(double radius, double theta, double phi)
{
	coord ccart1, ccart2;
	coordSphere csphere1, csphere2;
	int failure = 0;

	csphere1.vars.radius = radius;
	csphere1.vars.theta = theta;
	csphere1.vars.phi = phi;

	ccart1 = csphere1;
	csphere2 = ccart1;
	ccart2 = csphere2;

	// cout << ccart2 << "      " 
	cout << csphere1 << "   " << ccart1 << "   " << csphere2 << "   " << ccart2 << "   ";
	if (csphere1 == csphere2) {
		cout << "YES!" << endl;
	} else {
		cout << "NO!" << endl;
		failure = 1;
	}
	
	return failure;
}

int TestCoord(int failure)
{
	failure = RandomTestCoord(123123.0, 0.2, 0.4) || failure;
	failure = RandomTestCoord(12312.0, 0.3, 0.3) || failure;
	failure = RandomTestCoord(1231.0, 0.4, 0.2) || failure;
	failure = RandomTestCoord(123123123.0, 1.2, 1.4) || failure;
	failure = RandomTestCoord(12312312.0, 1.3, 1.3) || failure;
	failure = RandomTestCoord(1231231.0, 1.4, 1.2) || failure;
	
	cout << (const char *)(failure ? "FAILED" : "SUCCEEDED" ) << endl;	
	return failure;
}	



int TestSkills(void)
{
	int i, result, pts;
	
	Skills::Skill newSkill("unnamed");
	newSkill._ID = 1;
	newSkill._maxincr = 4;

	cout << endl;

	int lastResult = -10;
	for (i = -3; i <= 10; ++i) {
		pts = Skills::ModToPoints(newSkill, i);
		result = Skills::PointsToMod(newSkill, pts);
		if (result != lastResult) {
			// cout << i << ':' << result << ", ";
			lastResult = result;
		}
		cout << "MOD: " << i << "\tPTS:" << pts << "\tMOD:" << result << endl;
	}
	cout << endl;
	
	Skills::SkillStore	&store = *(Skills::SkillStore::Generate());
	store.SetSkill(newSkill, NULL, 2, 5);
	
	cout << endl;
	return 1;

}


typedef Templates::sorted_pointer_node_vector< int, float >	Bah;
struct testStruct
{
	SInt16 a;
	SInt8 d;
	SInt8 b;
	SInt32 c;
	SInt32 e;
	
	coordSphere coordA;
	World::Location l1;

	// Entity bA;	
	Thing tA;
};


int TestAccessors(void)
{
	Thing t;

	UInt8 *pGenus = (UInt8 *)t.GetPointer(GENUS);
	float *pMass = (float *)t.GetPointer(MASS);
	float *pTemperature = (float *)t.GetPointer(TEMPERATURE);

	cout << "Genus " << *pGenus << endl;
	cout << "Mass " << *pMass << endl;
	cout << "Temperature " << *pTemperature << endl;

	t.Set(GENUS, "THING");
	t.Set(MASS, "11.2");
	t.Set(TEMPERATURE, "98.6");

	cout << "Genus " << genusStrings[*pGenus] << endl;
	cout << "Mass " << *pMass << endl;
	cout << "Temperature " << *pTemperature << endl;

	return 0;
}

#if 0
int TestWeakRefs(void)
{
	class NewThing : public Thing 
	{
		virtual const char *				GetName(void) const					{	return "Humbug";		}
	};


	Thing *t1 = new Thing;
	Thing *t2 = new NewThing;
	Thing t3;
	WeakRef<Thing>	ref1;
	WeakRef<Thing>	ref2;
	WeakRef<Thing>	ref3;
	Thing *pThing;
	
	t1->SetName("t1");
	t2->SetName("t2");
	t3.SetName("t3");
	
	cout << "TestWeakRefs" << endl;

	cout << "ref1 " << &ref1 << " has address " << *ref1 << " with reference count " << ref1.Count() << endl;
	cout << "ref2 " << &ref2 << " has address " << *ref2 << " with reference count " << ref2.Count() << endl;

	ref1 = t1;
	ref1.Clear();
	ref1 = t1;
	cout << "ref1 " << &ref1 << " has address " << *ref1 << " with reference count " << ref1.Count() << endl;
	cout << "ref2 " << &ref2 << " has address " << *ref2 << " with reference count " << ref2.Count() << endl;
	ref2 = t1;
	cout << "ref1 " << &ref1 << " has address " << *ref1 << " with reference count " << ref1.Count() << endl;
	cout << "ref2 " << &ref2 << " has address " << *ref2 << " with reference count " << ref2.Count() << endl;
	
	ref1.Clear();
	cout << "ref1 " << &ref1 << " has address " << *ref1 << " with reference count " << ref1.Count() << endl;
	cout << "ref2 " << &ref2 << " has address " << *ref2 << " with reference count " << ref2.Count() << endl;
	if (ref2) {
		cout << "ref2 is set" << endl;
	} else {
		cout << "ref2 is clear" << endl;
	}
	
	pThing = *ref2;
	if (pThing)	cout << pThing->GetName() << endl;
	
	delete t1;
	ref2 = t2;
	pThing = *ref2;
	if (pThing)	{
		cout << pThing->GetName() << endl;
	} else {
		cout << "There's nothing there." << endl;
		ref2.Clear();
	}
	t1 = NULL;
	cout << "ref1 " << &ref1 << " has address " << *ref1 << " with reference count " << ref1.Count() << endl;
	cout << "ref2 " << &ref2 << " has address " << *ref2 << " with reference count " << ref2.Count() << endl;
	
	if (ref2) {
		cout << "ref2 is set" << endl;
	} else {
		cout << "ref2 is clear" << endl;
	}
	
	ref2.Clear();
	
	ref1 = t3;
	ref2 = t3;

	if (t1)	delete t1;
	if (t2)	delete t2;
	cout << "Things cleared." << endl;

	cout << "ref1 " << &ref1 << " has address " << *ref1 << " with reference count " << ref1.Count() << endl;
	cout << "ref2 " << &ref2 << " has address " << *ref2 << " with reference count " << ref2.Count() << endl;
	cout << "ref3 " << &ref3 << " has address " << *ref3 << " with reference count " << ref3.Count() << endl;

	if (ref1)	ref1.Clear();
	if (ref2)	ref2.Clear();
	if (ref3)	ref3.Clear();
	cout << "References cleared." << endl;
	return 0;	
}
#endif

int TestVectors(void)
{
	int i;
	float f1, f2, f3, *f;
	Bah	bahvector;

	f1 = 1.4;
	f2 = 3.2;
	f3 = 2.24;
	
	cout << "Size: " << bahvector.size() << endl;
	bahvector.Insert(1, f1);
	cout << "Size: " << bahvector.size() << endl;
	
	bahvector.Insert(0, f2);
	bahvector.Insert(4, f3);

	cout << "Size: " << bahvector.size() << endl;
	for (i = 0; i < bahvector.size(); i++) {
		f = bahvector[i].ptr;
		cout << '[' << i << "]  " << bahvector[i].key << "  " << *f << endl;
	}

	f = bahvector.GetByKey(1);
	if (f)	cout << "f " << *f << endl;		else cout << "Bah!" << endl;
	f = bahvector.GetByKey(4);
	if (f)	cout << "f " << *f << endl;		else cout << "Bah!" << endl;
	f = bahvector.GetByKey(3);
	if (f)	cout << "f " << *f << endl;		else cout << "Bah!" << endl;
	
	return 0;
}

int main(int argc, char *argv[])
{
	Base::Init();
	Things::Init();
	Worlds::Init();
	int failure = 0;

	TestToFrom();
	TestCoord(0); 

	TestAccessors();
	TestSkills();
	TestVectors();
	
	// TestWeakRefs();
	
	// cout << sizeof( long double ) << endl;
	
	return failure;
}


