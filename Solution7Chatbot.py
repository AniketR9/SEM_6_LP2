def to_lowercase(s):
    return s.lower()

def greet():
    greeting="Hello! Welcome to our electronics store"
    return greeting

def answer(u_input):
    responses={
        'delivery times': 'We usually deliver all our products within 7 business days',
        'return policy': 'Our store has a policy of accepting returns within 30 business days',
        'discount offers': 'You can view the discounts offered by our store on the Offers page of our website',
        'product information': 'We sell smartphones, laptops and  televisions',
        "order status": "To check your order status, can I get your order number?",
        'smartphones information': 'We offer a wide range of smartphone brands ranging from Apple, Samsung and Xiaomi',
        'laptops information' : 'We offer you a choice of brands ranging from SUS, DELL, HP and Apple',
        'televisions information': 'We offer you a choice of brands ranging from LG, Samsung, Redmi',
        "apple smartphones": "We have the latest iPhone models including the iPhone 15, iPhone 15 Pro, and iPhone 15 Pro Max. For more details pls visit our website",
        "samsung smartphones": "Discover our selection of Samsung Galaxy smartphones including the Galaxy S21, Galaxy S21+, and Galaxy S21 Ultra. For more details pls visit our website",
        "oneplus smartphones": "Check out our collection of OnePlus smartphones including the OnePlus 9 and OnePlus 9 Pro. For more details pls visit our website",
        "complaint regarding item":'We are sorry to hear that. Please share your concerns through the Issues page and we will do our best to help you'
    }
    best_match=None
    best_match_score=0
    for key,value in responses.items():
        score=sum(word in to_lowercase(u_input) for word in to_lowercase(key).split())
        if score>best_match_score:
            best_match=key
            best_match_score=score

    if best_match:
        response=responses[best_match]
        if best_match=='order status':
            onumber=input('Chatbot:',response)
            response=f"We cannot access the specific order details associated with order number {onumber} yet. But you will get a confirmed response within an hour. Kindly keep checking your account until then."
    else:
        response="I'm sorry! I didn't understand your request. Could you kindly rephrase it?"
    return response

def main():
    print(greet())
    while True:
        u_input = input("Customer: ")
        if u_input.lower() == "bye":
            print("Myntra Rep: Thank you for contacting us! Have a great day.")
            break
        print("Myntra Rep:", answer(u_input))


main()