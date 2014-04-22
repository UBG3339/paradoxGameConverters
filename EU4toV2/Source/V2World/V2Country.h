#ifndef V2COUNTRY_H_
#define V2COUNTRY_H_



#include "../Mapper.h"
#include "../Date.h"
#include "../Eu4World/EU4Army.h"
#include "V2Inventions.h"
#include "V2TechSchools.h"
#include <vector>
using namespace std;

class EU4World;
class EU4Country;
class V2World;
class V2State;
class V2Province;
class V2Relations;
class V2Army;
class V2Reforms;
class V2UncivReforms;
class V2Factory;
class V2Creditor;
class V2Leader;
class V2LeaderTraits;
struct V2Party;



class V2Country
{
	public:
		V2Country(string _tag, string _commonCountryFile, vector<V2Party*> _parties, V2World* _theWorld);
		void								output() const;
		void								initFromEU4Country(const EU4Country* _srcCountry, vector<string> outputOrder, countryMapping countryMap, cultureMapping cultureMap, religionMapping religionMap, unionCulturesMap unionCultures, governmentMapping governmentMap, inverseProvinceMapping inverseProvinceMap, vector<V2TechSchool> techSchools, map<int,int>& leaderMap, const V2LeaderTraits& lt);
		void								initFromHistory();
		void								addState(V2State* newState);
		void								convertArmies(const map<int,int>& leaderIDMap, double cost_per_regiment[num_reg_categories], const inverseProvinceMapping& inverseProvinceMap, map<int, V2Province*> allProvinces, vector<int> port_whitelist);
		bool								addFactory(V2Factory* factory);
		void								addRailroadtoCapitalState();
		void								convertUncivReforms();
		void								setupPops(EU4World& sourceWorld);
		void								setArmyTech(double mean, double scale, double stdDev);
		void								setNavyTech(double mean, double scale, double stdDev);
		void								setCommerceTech(double mean, double scale, double stdDev);
		void								setIndustryTech(double mean, double scale, double stdDev);
		void								setCultureTech(double mean, double scale, double stdDev);

		V2Relations*					getRelations(string withWhom) const;
		void								getNationalValueScores(int& liberty, int& equality, int& order);
		
		void								addProvince(V2Province* _province)		{ provinces.push_back(_province); };
		void								addPrestige(double additionalPrestige) { prestige += additionalPrestige; };
		void								addResearchPoints(double newPoints)		{ researchPoints += newPoints; };
		void								addTech(string newTech)						{ techs.push_back(newTech); };
		void								setNationalValue(string NV)				{ nationalValue = NV; };

		vector<V2Province*>			getProvinces() const { return provinces; };
		string							getTag() const { return tag; };
		bool								isCivilized() const { return civilized; };
		string							getPrimaryCulture() const { return primaryCulture; };
		vector<string>					getAcceptedCultures() const { return acceptedCultures; };
		const EU4Country*				getSourceCountry() const { return srcCountry; };
		inventionStatus				getInventionState(vanillaInventionType invention) const { return vanillaInventions[invention]; };
		inventionStatus				getInventionState(HODInventionType invention) const { return HODInventions[invention]; };
		double							getReactionary() const { return upperHouseReactionary; };
		double							getConservative() const { return upperHouseConservative; };
		double							getLiberal() const { return upperHouseLiberal; };
		vector< pair<int, int> >	getReactionaryIssues() const { return reactionaryIssues; };
		vector< pair<int, int> >	getConservativeIssues() const { return conservativeIssues; };
		vector< pair<int, int> >	getLiberalIssues() const { return liberalIssues; };
		double							getLiteracy() const { return literacy; };
		int								getCapital() const { return capital; };
	private:
		void			outputTech(FILE*) const ;
		void			outputElection(FILE*) const;
		void			sortRelations(const vector<string>& order);
		void			addLoan(string creditor, double size, double interest);
		int			addRegimentToArmy(V2Army* army, RegimentCategory rc, const inverseProvinceMapping& inverseProvinceMap, map<int, V2Province*> allProvinces);
		vector<int>	getPortProvinces(vector<int> locationCandidates, map<int, V2Province*> allProvinces);
		V2Army*		getArmyForRemainder(RegimentCategory rc);
		V2Province*	getProvinceForExpeditionaryArmy();

		V2World*							theWorld;
		const EU4Country*				srcCountry;
		string							filename;

		string							tag;
		vector<V2State*>				states;
		vector<V2Province*>			provinces;
		int								capital;
		bool								civilized;
		string							primaryCulture;
		vector<string>					acceptedCultures;
		string							religion;
		vector<V2Party*>				parties;
		string							rulingParty;
		string							commonCountryFile;
		double							prestige;
		double							leadership;
		double							plurality;
		vector<string>					techs;
		inventionStatus				vanillaInventions[VANILLA_naval_exercises];
		inventionStatus				HODInventions[HOD_naval_exercises];
		V2UncivReforms*				uncivReforms;
		double							researchPoints;
		string							techSchool;
		string							government;
		int								upperHouseReactionary;
		int								upperHouseConservative;
		int								upperHouseLiberal;
		vector< pair<int, int> >	reactionaryIssues;
		vector< pair<int, int> >	conservativeIssues;
		vector< pair<int, int> >	liberalIssues;
		vector<V2Relations*>			relations;
		vector<V2Army*>				armies;
		V2Reforms*						reforms;
		string							nationalValue;
		double							money;
		date								lastBankrupt;
		map<string, V2Creditor*>	creditors;
		double							bankReserves;
		double							diploPoints;
		double							badboy;
		vector<V2Leader*>				leaders;
		double							literacy;
};

bool ProvinceRegimentCapacityPredicate(V2Province* prov1, V2Province* prov2);


#endif	// V2COUNTRY_H_