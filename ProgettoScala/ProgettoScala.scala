import scala.collection.mutable._

// sealed trait, `e risultato utile usarlo in quanto tutte le possibili combinazioni di ingredienti del bubble tea
// sono state definite precedentemente di conseguenza, tutti i membri del trait sono gia` stati 
// definiti ed il compilatore li conosce in anticipo.
sealed trait Topping
case object Panna extends Topping
case object Marshmallow extends Topping
case object Zuccherini extends Topping
case object NoTopping extends Topping

sealed trait Bolle
case object Mango extends Bolle
case object Mirtillo extends Bolle
case object Fragola extends Bolle
case object MelaVerde extends Bolle
case object Litchi extends Bolle

sealed trait Te
case object TeVerde extends Te
case object TeNero extends Te
case object TeRosso extends Te

class BubbleTea (var tipoTe: Te, var bolle: ArrayBuffer[Bolle], var topping: Topping){

    def aggiungiBolle(b: Bolle): Unit ={
        bolle += b
        println("Hai aggiunto le bolle "+b)
    } 
    def rimuoviBolle(b: Bolle): Unit ={
        bolle -= b
        println("Hai rimosso le bolle "+b)
        }
    def rimuoviTutteBolle(): Unit = {
        println("Hai rimosso tutte le bolle")
        bolle.clear()
        }

    def printTea():String = {
      var s:String ="Te: "+this.tipoTe+"\nBolle: "

      for(x <- this.bolle){
        s+=x.toString()+" "
      }
      s+="\nTopping: "+this.topping

      return s
    }
    
}

class Ordine (var tbubbleTea: ArrayBuffer[BubbleTea], var cliente: Cliente){

    def addBubbleTea(p: BubbleTea): Unit = tbubbleTea += p
    def removeBubbleTea(p: BubbleTea): Unit = tbubbleTea -= p

    // Otteniamo prezzo base
    def getBasePrice(p: BubbleTea): Double = {

      var prezzo:Double = 0.0

        p.tipoTe match {

          case TeRosso => prezzo+=1.5
          case TeVerde => prezzo+=1
          case TeNero => prezzo+=1
        }
        for(x <- p.bolle){
          x match {
            case Mango => prezzo+=1.5
            case Mirtillo => prezzo+=1
            case Fragola => prezzo+=0.5
            case MelaVerde => prezzo+=1
            case Litchi => prezzo+=2

          }
        }
        p.topping match {
            case  Panna => prezzo+=1
            case  Marshmallow => prezzo+=1
            case  Zuccherini => prezzo+=0.5
            case  NoTopping => prezzo+=0
        }
        
      return prezzo
    }
    // Otteniamo prezzo totale
    def getTotalPrice(): Double = {

      var prezzoOrdine:Double = 0.0

        for(p <- tbubbleTea){
                    p.tipoTe match {

          case TeRosso => prezzoOrdine+=1.5
          case TeVerde => prezzoOrdine+=1
          case TeNero => prezzoOrdine+=1
        }
        for(x <- p.bolle){
          x match {
            case Mango => prezzoOrdine+=1.5
            case Mirtillo => prezzoOrdine+=1
            case Fragola => prezzoOrdine+=0.5
            case MelaVerde => prezzoOrdine+=1
            case Litchi => prezzoOrdine+=2

          }
        }
        p.topping match {
            case  Panna => prezzoOrdine+=1
            case  Marshmallow => prezzoOrdine+=1
            case  Zuccherini => prezzoOrdine+=0.5
            case  NoTopping => prezzoOrdine+=0
        }
        }
      return prezzoOrdine
    }

}
class Cliente ( var nome: String,var telefono: String,  var cartaFedelta: String)
  def getName = this.nome
  def getFidelity = this.cartaFedelta
object Main {
  def main(args: Array[String]): Unit = {

     val p1 = new BubbleTea (
        TeVerde,
        ArrayBuffer(Mango,Mirtillo),
        Panna
    )
    val p2 = new BubbleTea (TeRosso, ArrayBuffer(MelaVerde),NoTopping)
    val cliente = new Cliente("Daniele","0023","1234")

    val ordine = new Ordine(ArrayBuffer(p1,p2),cliente)
    println("Creazione ordine: ")
    println("Primo: "+p1.printTea()+" prezzo: "+ordine.getBasePrice(p1))
    println("Secondo: "+p2.printTea()+" prezzo: "+ordine.getBasePrice(p2))
    println("prezzo totale: "+ordine.getTotalPrice())

  }
}
