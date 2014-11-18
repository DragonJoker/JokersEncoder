#pragma once

namespace Joker
{
	/*!
	Classe permettant de créer une classe avec un objet unique
	\author Sylvain DOREMUS
	\date 22/11/2011
	*/
	template< class T >
	class JGRA_API CAutoSingleton
	{
	protected:
		CAutoSingleton() {}
		~CAutoSingleton() {}

	private:
		/**
		 * Constructeur par copie privé afin de ne pas pouvoir le copier( il est censé être unique )
		 */
		CAutoSingleton( CAutoSingleton const & );
		/**
		 * Opérateur de copie privé afin de ne pas pouvoir le copier( il est censé être unique )
		 */
		CAutoSingleton const & operator =( CAutoSingleton const & );

	public:
		/**
		 *\return Le singleton( l'instance unique ), qui est créé si il n'existe pas encore
		 */
		static T & GetSingleton()
		{
			static T m_singleton;
			return m_singleton;
		}
		/**
		 *\return Le pointeur sur le singleton( l'instance unique ), qui est créé si il n'existe pas encore
		 */
		static T * GetSingletonPtr()
		{
			return & GetSingleton();
		}
	};
}