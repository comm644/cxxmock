

namespace CxxMock {

class ArgList;

	struct IAction 
	{
		virtual void call(IArgumentPtr result, const ArgList& args) = 0;
		virtual ~IAction() {};
	};

	template< typename Sender, typename T>
	class Action : public IAction
	{
		Sender* _sender;
		T _method;
	public:
		Action(Sender* sender, T method ): _sender(sender), _method( method ){}

        // ---------- non-void methods

		template<typename R>
		void callMethod(IArgumentPtr result, const ArgList& args, R (Sender::*method)()){
		    result->setValue(Argument<R>((_sender->*_method)()));
		}

		template<typename R, typename A>
		void callMethod(IArgumentPtr result, const ArgList& args, R (Sender::*method)(A)){
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0) )) );
		}

		template<typename R, typename A, typename B>
		void callMethod(IArgumentPtr result, const ArgList& args, R (Sender::*method)(A,B)){
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1))) );
		}

		template<typename R, typename A, typename B, typename C>
		void callMethod(IArgumentPtr result,const ArgList& args, R (Sender::*method)(A,B,C)){   
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2) )));
		}

		template<typename R, typename A, typename B, typename C, typename D>
		void callMethod(IArgumentPtr result,const ArgList& args, R (Sender::*method)(A,B,C,D)){   
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3) )));
		}


		template<typename R, typename A, typename B, typename C, typename D, typename E>
		void callMethod(IArgumentPtr result,const ArgList& args, R (Sender::*method)(A,B,C,D,E)){   
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4)))); 
		}

		template<typename R, typename A, typename B, typename C, typename D, typename E, typename F>
		void callMethod(IArgumentPtr result,const ArgList& args, R (Sender::*method)(A,B,C,D,E,F)){   
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5)))); 
		}

		template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, 
		                     typename G>
		void callMethod(IArgumentPtr result,const ArgList& args, R (Sender::*method)(A,B,C,D,E,F,G)){   
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5), 
		                         args.val<G>(6)))); 
		}

		template<typename R, typename A, typename B, typename C, typename D, typename E, typename F,
 		                     typename G, typename H>
		void callMethod(IArgumentPtr result,const ArgList& args, R (Sender::*method)(A,B,C,D,E,F,G,H)){   
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5), 
		                         args.val<G>(6), args.val<H>(7))));  
		}


		template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, 
		                     typename G, typename H, typename I>
		void callMethod(IArgumentPtr result,const ArgList& args, R (Sender::*method)(A,B,C,D,E,F,G,H,I)){   
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5), 
		                         args.val<G>(6), args.val<H>(7), args.val<I>(8))));
		}

		template<typename R, typename A, typename B, typename C, typename D, typename E, typename F, 
		                     typename G, typename H, typename I, typename J>
		void callMethod(IArgumentPtr result,const ArgList& args, R (Sender::*method)(A,B,C,D,E,F,G,H,I,J)){   
		    result->setValue(Argument<R>((_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5), 
		                         args.val<G>(6), args.val<H>(7), args.val<I>(8), args.val<J>(9)))); 
		}

        // ---------- void methods

		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)()){
		    (_sender->*_method)();
		}

		template<typename A>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A)){
		    (_sender->*_method)( args.val<A>(0) );
		}

		template<typename A, typename B>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1)); 
		}

		template<typename A, typename B, typename C>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B,C)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2));
		}

		template<typename A, typename B, typename C, typename D>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B,C,D)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3));
		}


		template<typename A, typename B, typename C, typename D, typename E>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B,C,D,E)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4));
		}

		template<typename A, typename B, typename C, typename D, typename E, typename F>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B,C,D,E,F)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5));
		}

		template<typename A, typename B, typename C, typename D, typename E, typename F, 
		                     typename G>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B,C,D,E,F,G)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5), 
		                         args.val<G>(6));
		}

		template<typename A, typename B, typename C, typename D, typename E, typename F,
 		                     typename G, typename H>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B,C,D,E,F,G,H)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5), 
		                         args.val<G>(6), args.val<H>(7));
		}


		template<typename A, typename B, typename C, typename D, typename E, typename F, 
		                     typename G, typename H, typename I>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B,C,D,E,F,G,H,I)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5), 
		                         args.val<G>(6), args.val<H>(7), args.val<I>(8));
		}

		template<typename A, typename B, typename C, typename D, typename E, typename F, 
		                     typename G, typename H, typename I, typename J>
		void callMethod(IArgumentPtr result,const ArgList& args, void (Sender::*method)(A,B,C,D,E,F,G,H,I,J)){   
		    (_sender->*_method)( args.val<A>(0), args.val<B>(1), args.val<C>(2), args.val<D>(3), args.val<E>(4), args.val<F>(5), 
		                         args.val<G>(6), args.val<H>(7), args.val<I>(8), args.val<J>(9));
		}


		void call(IArgumentPtr result, const ArgList& args)
		{
		    callMethod(result, args, _method );
		}

	};
}
